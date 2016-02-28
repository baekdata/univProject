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
		// DB ������ ȹ��(DB �α���)
		Class.forName("oracle.jdbc.driver.OracleDriver");// ������ .class������
															// ã�Ƽ� Driver
															// Manager����
															// ����ϴ� ����
		conn = DriverManager.getConnection(
				"jdbc:oracle:thin:@210.94.199.20:1521:DBLAB", "ST2010112391", "ST2010112391");
		return conn;
	}

	public static void close(Connection conn, PreparedStatement stmt) {
		// ���� ���ҽ��� ����(close)
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
