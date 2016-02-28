<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.util.*"%>
<%@page import="vo.*" %>
<%@page import="java.text.*" %>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
  String session_id = (String)session.getAttribute("user");
 // int notice_idx = Integer.parseInt(request.getParameter("notice_idx"));
  //int start_date = Integer.parseInt(request.getParameter("apply_start_date"));
  
  /*
  String dateString = request.getParameter("apply_start_date");
  java.text.DateFormat df = new java.text.SimpleDateFormat("MM/dd/yyyy");
  java.util.Date d = df.parse(dateString);
  java.sql.Date dateSql = new java.sql.Date(d.getTime());
*/
  
  SimpleDateFormat formatador = new SimpleDateFormat("MM/dd/yyy");  
  Date dataf;  
  String aux = "15/10/1988";  
  try{  
  DateFormat di = DateFormat.getDateInstance();  
  dataf = di.parse(aux);  
  aux = formatador.format(dataf);  
  Date date = di.parse(aux);
  java.sql.Date dateSql = new java.sql.Date(date.getTime());
  }  
  catch(ParseException e){e.printStackTrace();}  
/*
  String dateStr = request.getParameter("apply_start_date");
  DateFormat df = DateFormat.getDateInstance(DateFormat.LONG, Locale.KOREA);
  Date date = df.parse(dateStr);
  java.sql.Date dateSql = new java.sql.Date(date.getTime());
  */
  String dateStr2 = request.getParameter("apply_end_date");
  DateFormat df2 = DateFormat.getDateInstance(DateFormat.LONG, Locale.KOREA);
  //Date date2 = df2.parse(dateStr2);
 // java.sql.Date dateSql2 = new java.sql.Date(date2.getTime());

  int spec_code = Integer.parseInt(request.getParameter("spec_name"));
  String spec_level = request.getParameter("spec_level");
  
  String apply_name = request.getParameter("apply_name");
  apply_name = new String(apply_name .getBytes("8859_1"), "UTF-8");
  
  String apply_contents = request.getParameter("apply_contents");
  apply_contents = new String(apply_contents .getBytes("8859_1"), "UTF-8");
  int apply_state=1;
  
  String from = request.getParameter("apply_start_date");
  SimpleDateFormat transFormat = new SimpleDateFormat("yyyy-MM-dd");
  Date to = transFormat.parse(from);
  java.sql.Date to2 = new java.sql.Date(to.getTime());
  
  String from2 = request.getParameter("apply_end_date");
  SimpleDateFormat transFormat2 = new SimpleDateFormat("yyyy-MM-dd");
  Date to4 = transFormat.parse(from2);
  java.sql.Date to3 = new java.sql.Date(to4.getTime());

  
  if(session_id == null ){
%>
	<script>
		alert("회원만 질문을 할 수 있습니다.");
		location.href = "login.jsp";
	</script>
<%		  
  }else {
	  String result = ctrl.insertNotice(session_id, to2, to3, apply_name, apply_state, spec_code, spec_level, apply_contents);
%>
	  <script>
	  	alert("<%=result%>");
	  	location.href="company_apply_add.jsp?idx="+<%=3%>+"&type="+<%=2%>;
	  </script>
<%
  }
%>
  
  