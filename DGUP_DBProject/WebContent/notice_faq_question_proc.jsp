<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>

<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
  String session_id = (String)session.getAttribute("user");
  int noticeIDX = Integer.parseInt(request.getParameter("notice_idx"));
  
  int type = Integer.parseInt(request.getParameter("type"));
  String faq_contents = request.getParameter("faq_contents");
  faq_contents = new String(faq_contents .getBytes("8859_1"), "UTF-8"); //한글처리

  if(session_id == null ){
%>
	<script>
		alert("회원만 질문을 할 수 있습니다.");
		location.href = "login.jsp";
	</script>
<%		  
  } else {
	  String result = ctrl.insertQuestion(session_id, noticeIDX, faq_contents);
%>
	  <script>
	  	location.href="notice_detail.jsp?idx="+<%=noticeIDX%>+"&type="+<%=type%>;
	  </script>
<%
  }
%>