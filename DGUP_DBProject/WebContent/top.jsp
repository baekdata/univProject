<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
	String session_id = (String)session.getAttribute("user");
	int session_flag=0;
	if (session_id!=null) { 
		session_flag = (Integer)session.getAttribute("flag");
	}
%>
<nav class="navbar navbar-inverse" style="margin-bottom:0px;">
  
  <div class="container">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <span class="navbar-brand">DGUP</span> 
    </div>
    <div id="navbar" class="navbar-collapse collapse">
    	<ul class="nav navbar-nav">
            <li><a href="./">홈</a></li>
<%
	if(session_id!=null && session_flag == 1) {
%>
        <li><a href="./spec.jsp">스펙관리</a></li>
<%	
	} else if(session_id!=null && session_flag == 2){
%>
            <li><a href="./company_mgr.jsp">공고관리</a></li>
<%
	}
%>
          </ul>
      <form class="navbar-form navbar-right">
<%
	if (session_id==null) {  
%>
        <button id="login_btn" type="button" class="btn btn-danger">로그인</button>
        <button id="signin_btn" type="button" class="btn btn-success">회원가입</button>
<%
	} else {
%>	 
		<button id="logout_btn" type="button" class="btn btn-success">로그아웃</button>
<%
	}
%>
      </form>
    </div>
  </div>
</nav>


