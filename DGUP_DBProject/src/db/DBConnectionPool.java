package db;

import java.sql.* ;
import java.util.* ;

public class DBConnectionPool {
	private static DBConnectionPool instance ;
	private Driver driver ;
	private String url ;
	private String user ;
	private String passwd ;
    private int activatedCnt ;
    private int maxConnCnt ;
    private Vector <Connection> freeConns ;
	
	public static synchronized DBConnectionPool getInstance() {
		if(instance == null)
			instance = new DBConnectionPool() ;
		
		return instance ;
	}
	
	private DBConnectionPool() {
		createPool() ;
		this.freeConns = new Vector<Connection>() ;
		this.maxConnCnt = 150 ;
		this.activatedCnt = 0 ;
	}
	
	private void createPool() {
		try {
			this.url = "jdbc:oracle:thin:@210.94.199.20:1521:DBLAB" ;
			this.user = "ST2010112391" ;
			this.passwd = "ST2010112391" ;
			this.driver = (Driver)Class.forName("oracle.jdbc.driver.OracleDriver").newInstance() ;
			DriverManager.registerDriver(this.driver) ;
		} catch(Exception ex) {
			ex.printStackTrace() ;
		}
	}
	
	private Connection newConn() {
		Connection conn = null ;
		
		try {
			conn = DriverManager.getConnection(url, user, passwd) ;
			conn.setAutoCommit(false) ;
		} catch(SQLException ex) {
			ex.printStackTrace() ;
			return null ;
		}
		
		return conn ;
	}
	
    public synchronized void release() {
    	try {
    		Enumeration <Connection> allConns = freeConns.elements() ;
    	
    		while(allConns.hasMoreElements()) {
    			Connection conn = (Connection)allConns.nextElement() ;
    			conn.rollback() ;
    			conn.setAutoCommit(true) ;
    			conn.close() ;
    		}
    	
    		freeConns.removeAllElements() ;
    		DriverManager.deregisterDriver(this.driver);
    	} catch(SQLException ex) {
    		ex.printStackTrace() ;
    	}
	}
    
	public synchronized void freeConn(Connection conn) {
    	freeConns.addElement(conn) ;
    	activatedCnt-- ;
    	
        if(activatedCnt < 0) 
        	activatedCnt = 0 ;

        notifyAll() ;
    }
    
    public synchronized Connection getConn() {
    	Connection conn = null ;

        if(freeConns.size() > 0) {
        	conn = (Connection)freeConns.firstElement() ;
        	freeConns.removeElementAt(0) ;
        	
        	try {
        		if(conn.isClosed()) {
        			conn = getConn() ;
        		}
        	} catch(SQLException ex) {
        		ex.printStackTrace() ;
        	}
        } else if(maxConnCnt == 0 || activatedCnt < maxConnCnt) {
        	conn = newConn() ;
        } else if(activatedCnt == maxConnCnt) {
        	try {
        		wait() ;
        		conn = getConn() ;
        	} catch(InterruptedException ex) {
        		ex.printStackTrace() ;
        	}
        }

        if(conn != null) {
          activatedCnt++ ;
        }

        return conn ;
	}
    
    public static void main(String[] args) {
    	DBConnectionPool dbcp = DBConnectionPool.getInstance() ;
    	for(int i = 0 ; i < 2 ; i++)
    		System.out.println(dbcp.getConn()) ;
    }
}
