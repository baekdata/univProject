<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="java.util.*, vo.*"%>
<%@page import="java.text.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<%
	String idx = request.getParameter("noticeIDX");
	NoticeVo list = ctrl.noticeDetail(idx);
	int type = Integer.parseInt(request.getParameter("type"));
	//String type2 = request.getParameter("type");
	//int type=0;
	//if(type2 !=null){
		//type = Integer.parseInt(type2);
	//}else{
		//type =0;
	//}
	//String type = request.getParameter("type");
	DateFormat df = new SimpleDateFormat("dd/MM/yyy");
String tt = "04/26/2013 05:30 AM GMT -1200";
Date d= df.parse(tt);
java.sql.Date dateSql4 = new java.sql.Date(d.getTime());
	
%>
<!DOCTYPE html>
<html>
  <head>
    <title>DGUP</title>
    <!-- Bootstrap core CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap-theme.min.css">

    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>
	
    <%@ include file="top.jsp" %>
    <%
    	if (session_id==null) {
    		%>
    		<script>
    			alert("로그인 후 이용하세요");
    			location.href = "login.jsp";
    		</script>
    	<%	   		
	    	}
    		  	
    	%>
	
    <div class="container">
      <!-- Example row of columns -->
      
	  <br>
	  <p class="bg-info" style="padding: 15px;font-size: 17px;font-weight: bold;">
	  	 [<%=list.getCompany_name() %> 채용]<%=list.getNotice_name() %>모집
	  </p>
	  <blockquote style="font-size: 14.5px;">
		  <p>기업명 : <%=list.getCompany_name() %></p>
		  <p>업종/형태 : <%=list.getType_of_bussiness() %></p>
		  <p>공고명 : <%=list.getNotice_name() %></p>
		  <p>모집일자 : <%=list.getStart_date() %> - <%=list.getEnd_date() %></p>
      </blockquote><br>
      <p class="bg-warning" style="padding: 15px;font-size: 14px;">
	  	 <%=list.getNotice_contents() %>
	  </p>
	  <br>
	  
      <br>
      <form method="post" action="./notice_resume_proc.jsp" >
     	   <input type="hidden" name="notice_idx" value="<%=idx%>">  
     
		  <p class="bg-primary"  style="padding: 15px;font-size: 17px;font-weight: bold;">지원서</p>
		  <div class="row" style="padding-left:17px;">
	     		<textarea name="apply_contents" class="form-control" placeholder="지원서 내용을 입력해주세요" style="width: 98.9%;"></textarea>
	      </div>
		  <br>
	      <br>
	      <center><button type="submit" class="btn btn-success">지원하기</button></center>
      </form>

	 <hr>

      <footer>
        <p style="text-align: center;">Copyright 2015 DGUP Team. All right reserved</p>
      </footer>
    </div> 
    
    
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
	
	<script>
		$( document ).ready( function(){	
			$("#login_btn").click(function() {
				location.href="./login.jsp";
			});
			$("#signin_btn").click(function() {
				location.href="./join.jsp";
			});
			$("#logout_btn").click(function() {
				location.href="./logout.jsp";
			});			
		});
	</script>
  </body>
</html>
