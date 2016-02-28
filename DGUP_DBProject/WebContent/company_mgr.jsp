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
    
	<div class="jumbotron">
	   <div class="container">
	     <h1>지금 DGUP에 채용 공고를 등록하세요!</h1>
	   </div> 
	</div>

    <div class="container">
      <!-- Example row of columns -->
      <div class="row">
        <div class="col-sm-3 blog-sidebar">
          	<div class="list-group">
			  <a href="#" class="list-group-item active">공고 현황</a>
           	  <a href="./company_apply_add.jsp" class="list-group-item">공고 등록</a>
			</div>
        </div>
        
        <div class="col-sm-8 blog-main">

          <div class="blog-post">
            <h2 class="blog-post-title">등록한 공고 현황</h2>
            <table class="table table-bordered">
			  <thead>
			    <tr>
			      <th>#</th>
			      <th>공고명</th>
			      <th>공고시작</th>
			      <th>공고종료</th>
			    </tr>
			  </thead>
			  <tbody>
			  <%
				List<NoticeVo> list = ctrl.all_notice(session_id); //@@
				for(int i=0; i<list.size(); i++) {
				%>
			   <tr>
			      <th scope="row"><a href="./notice_detail.jsp?idx=<%=list.get(i).getNotice_idx()%>&type=-1"><%=i+1%></a></th>
			      <td><%=list.get(i).getNotice_name()%></td>
			      <td><a href="./company_apply_detail.jsp?idx=<%=list.get(i).getNotice_idx()%>"><%=list.get(i).getStart_date()%></a></td>
			      <td><%=list.get(i).getEnd_date()%></td>
			    </tr>
			  <%
				}
			%>
			  <!-- 
			    <tr>
			      <th scope="row">1</th>
			      <td>Mark</td>
			      <td>Otto</td>
			      <td>@mdo</td>
			    </tr>
			    <tr>
			      <th scope="row">2</th>
			      <td>Jacob</td>
			      <td>Thornton</td>
			      <td>@fat</td>
			    </tr>
			    <tr>
			      <th scope="row">3</th>
			      <td>Larry</td>
			      <td>the Bird</td>
			      <td>@twitter</td>
			    </tr>
			    
			     -->
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
