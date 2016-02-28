<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>
<%@page import="java.text.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
//request.setCharacterEncoding("EUC-KR");
  String session_id = (String)session.getAttribute("user");
  int noticeID = Integer.parseInt(request.getParameter("notice_idx"));
  String resumeContents = request.getParameter("apply_contents");
  resumeContents = new String(resumeContents .getBytes("8859_1"), "UTF-8"); //한글처리
  
  if(session_id == null ){
%>
	<script>
		alert("회원만 질문을 할 수 있습니다.");
		location.href = "login.jsp";
	</script>
<%		  
  } else {
	  String result = ctrl.insertApply(noticeID, session_id, resumeContents);
%>
	  <script>
	  	alert("<%=result%>");
	  	location.href="./";
	  </script>
<%
  }
%>