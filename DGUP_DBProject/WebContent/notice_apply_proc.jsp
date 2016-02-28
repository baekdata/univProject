<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>
<%@page import="java.text.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
//request.setCharacterEncoding("EUC-KR");
  String session_id = (String)session.getAttribute("user");
  String noticeID;
  String type;
  int noticeIDX=0;
 // int TYPE = 0;
  try{
	  noticeID = request.getParameter("noticeIDX");
	  noticeIDX = Integer.parseInt(noticeID);
	//  type = request.getParameter("TYPE");
 	//  TYPE = Integer.parseInt(type);
  }catch(Exception ex){
  
  }
 // String faq_contents = request.getParameter("apply_contents");
 //faq_contents = new String(faq_contents .getBytes("8859_1"), "UTF-8"); //한글처리
 /* String dateStr2 = request.getParameter("apply_date");
  java.sql.Date d = java.sql.Date.valueOf(dateStr2);		        //시스템의 현재 날짜 저장
	
  
  String  now2  = "20090320"; // SimpleDateFormat 생성자에 전달되는 형식과 일치해야 함
  java.util.Date d2 = new java.text.SimpleDateFormat("yyyyMMdd").parse(now2);
  java.sql.Date dateSql = new java.sql.Date(d2.getTime());
*/
DateFormat df = new SimpleDateFormat("dd/MM/yyy");
String tt = "04/26/2013 05:30 AM GMT -1200";
Date d= df.parse(tt);
java.sql.Date dateSql4 = new java.sql.Date(d.getTime());

  
  if(session_id == null ){
  }
%>
	<script>
		alert("회원만 질문을 할 수 있습니다.");
		location.href = "login.jsp";
	</script>
