<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
  String userID = request.getParameter("inputEmail");
  String userPassword = request.getParameter("inputPassword");
  String userType = request.getParameter("inlineRadioOptions");

  UserVo user = ctrl.LoginProc(userID, userPassword, userType);
  if(user.getEmail() == null ){
%>
	<script>
		alert("사용자아이디 혹은 암호가 틀렸습니다");
		location.href = "login.jsp";
	</script>
<%		  
  } else {

	  session.setAttribute("user", user.getEmail());
	  session.setAttribute("flag", user.getFlag());
      response.sendRedirect("index.jsp");
 
  }
%>
  
  
  