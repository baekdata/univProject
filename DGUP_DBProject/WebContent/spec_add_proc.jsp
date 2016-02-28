<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
  List<SpecVo> list = ctrl.getSpecList();
  String session_id = (String)session.getAttribute("user");
  //String spec_name = request.getParameter("spec_name");
  //int spec_code = Integer.parseInt(request.getParameter("spec_code").trim());
 // int spec_code = Integer.parseInt(request.getParameter("spec_name").trim()); //  code name으로 변경
  //String spec_name = request.getParameter(("specName").trim());
	//String number = request.getParameter(("specLevel").trim());
	//System.out.println(spec_name);
/*
	System.out.println(number);
 int spec_code =0;
 try{
 spec_code = Integer.parseInt(spec_name);
 }catch(Exception ex){}
 */
 //int spec_level = Integer.parseInt(request.getParameter("spec_level"));
	String spec_level = request.getParameter("spec_level").trim();
	spec_level = new String(spec_level .getBytes("8859_1"), "UTF-8"); //한글처리

	//if (number == null) {
	//number = "0";
	//}
	//int num = Integer.parseInt(number);
	
  if(session_id == null ){
%>
	<script>
		alert("회원만 스펙을 등록할 수 있습니다.");
		location.href = "login.jsp";
	</script>
<%		  
  } else {
	  String result = ctrl.insertSpec(1011, spec_level, session_id);
%>
	  <script>
	  	alert("<%=result%>");
	  	location.href="spec_add.jsp?idx="+<%=3%>+"&type="+<%=2%>;
	  </script>
<%
  }
%>