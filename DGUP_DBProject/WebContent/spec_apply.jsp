<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>

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
	<div class="jumbotron">
	   <div class="container">
	     <h1>지금 DGUP에 스팩을 등록하세요!</h1>
	     <p>자신의 스팩에 맞는 회사의 채용 공고를 볼 수 있습니다.</p>
	   </div> 
	</div>

    <div class="container">
      <!-- Example row of columns -->
      <div class="row">
        <div class="col-sm-3 blog-sidebar">
          	<div class="list-group">
			  <a href="./spec.jsp" class="list-group-item ">스팩 현황</a>
           	  <a href="./spec_add.jsp" class="list-group-item">스팩 등록</a>
           	  <a href="#" class="list-group-item active">지원 현황</a>
			</div>
        </div>
        
        <div class="col-sm-8 blog-main">

          <div class="blog-post">
            <h2 class="blog-post-title">지원한 회사 현황</h2>
            <table class="table table-bordered">
			  <thead>
			    <tr>
			      <th>#</th>
			      <th>지원회사</th>
			      <th>공고명</th>
			      <th>지원일자</th>
			      <th>상태</th>
			    </tr>
			  </thead>
			  <tbody>
<%
	List<ApplyVo> list = ctrl.getApplyList(session_id);
	for(int i=0; i<list.size(); i++) {
		
%>
			  <tr>
			      <th scope="row"><%=i+1 %></th>
			      <td><%=list.get(i).getCompanyName() %></td>
			      <td><%=list.get(i).getApplyName() %></td>
			      <td><%=list.get(i).getApplyDate() %></td>
			      <%
			      	if(list.get(i).getStatus()==0) {
			      %>
			      		<td>진행중</td>
			      <%		
			      	} else if(list.get(i).getStatus()==1) {
			      %>
			      		<td>합격</td>
			      <%		
			      	} else if(list.get(i).getStatus()==2) {
			      %>
			      		<td>불합격</td>
			      <%		
			      	}
			      %>
			      
			    </tr>
<%
	}
%>
			  </tbody>
			</table>
          </div>  
	
        </div>
      </div>

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
