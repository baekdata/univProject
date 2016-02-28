<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
 
  String session_id = (String)session.getAttribute("user");
	int noticeID = Integer.parseInt(request.getParameter("idx"));
	int seeker = Integer.parseInt(request.getParameter("seeker"));
	int type = Integer.parseInt(request.getParameter("type1"));
	
  if(session_id == null){
%>
	<script>
		alert("비정상적인 접근입니다.");
		location.href = "login.jsp";
	</script>
<%		  
  } else {
	  String result = ctrl.applyProc(type, seeker);
%>
	  <script>
	  	alert("<%=result%>");
	  	location.href="company_apply_detail.jsp?idx="+<%=noticeID%>;
	  </script>
<%
  }
%>