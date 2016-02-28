<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
<html><head><title> 수강신청 입력 </title></head>
<body>

<%@ include file="top.jsp" %>


<table width="75%" align="center" border> <br>
	<tr><th>과목번호</th><th>분반</th><th>과목명</th><th>학점</th><th>수강신청</th></tr>
<%
	Connection myConn = null;
	ResultSet myResultSet =null;
	PreparedStatement pstmt = null;
	String mySQL = "";
	String dburl = "jdbc:oracle:thin:@210.94.199.20:1521:DBLAB";
	String user="ST2010112419";
	String passwd = "ST2010112419";
	String dbdriver = "oracle.jdbc.driver.OracleDriver";

	try {
		Class.forName(dbdriver);
		myConn = DriverManager.getConnection(dburl, user, passwd);
	} catch(SQLException ex) {
		System.err.println("SQLException : "+ ex.getMessage());
	}

	//mySQL = "select * from course ";
	// mySQL = "select * from course where c_id not in "+
	//  		"(select c_id from enroll where s_id = '" + session_id + "' or e_year !='2015' or e_semester!='2')" +
	//  		" and c_id in "+
	// 		"(select c_id from teach where t_year ='2015' and t_semester ='2')";
	try {
		mySQL = "select * from course where c_id not in "+
	 		"(select c_id from enroll where s_id=? or e_year!=? or e_semester!=?)" +
	 		" and c_id in "+
			"(select c_id from teach where t_year=? and t_semester=?)";

	
		pstmt = myConn.prepareStatement(mySQL);

		pstmt.setString(1, session_id);
		pstmt.setString(2, "2015");
		pstmt.setString(3, "2");
		pstmt.setString(4, "2015");
		pstmt.setString(5, "2");

		myResultSet = pstmt.executeQuery();
			
	} catch(Exception ex) {
		ex.printStackTrace();
		System.err.println("SQLException : "+ ex.getMessage());
	}
	
	//Statement stmt = myConn.createStatement();
	//myResultSet = stmt.executeQuery(mySQL);

	if(myResultSet != null) {

		while(myResultSet.next()) {

			String c_id = myResultSet.getString("c_id");
			int c_id_no = myResultSet.getInt("c_id_no");
			String c_name = myResultSet.getString("c_name");
			int c_unit = myResultSet.getInt("c_unit");
%>
	<tr>
		<td align="center"><%= c_id %></td>
		<td align="center"><%= c_id_no %></td>
		<td align="center"><%= c_name %></td>
		<td align="center"><%= c_unit %></td>
		<td align="center"><a href="insert_verify.jsp?c_id=<%= c_id %>&c_id_no=<%= c_id_no %>">신청</a></td>
	</tr>
<%
		}
	}


	pstmt.close();
	myConn.close();
%>
</table></body></html>
