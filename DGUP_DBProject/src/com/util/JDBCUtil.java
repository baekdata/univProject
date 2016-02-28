package com.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class JDBCUtil {
	public static Connection getConnection() throws ClassNotFoundException,
			SQLException {
		Connection conn;
		// DB 컨낵션 획득(DB 로그인)
		Class.forName("oracle.jdbc.driver.OracleDriver");// 물리적 .class파일을
															// 찾아서 Driver
															// Manager한테
															// 등록하는 역할
		conn = DriverManager.getConnection(
				"jdbc:oracle:thin:@210.94.199.20:1521:DBLAB", "ST2010112391", "ST2010112391");
		return conn;
	}

	public static void close(Connection conn, PreparedStatement stmt) {
		// 각종 리소스를 해제(close)
		if (stmt != null) {
			try {
				stmt.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (conn != null) {
			try {
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public static void close(Connection conn, PreparedStatement stmt,
			ResultSet rs) {
		close(conn, stmt);
		if (rs != null) {
			try {
				rs.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
