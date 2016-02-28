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
			  <a href="./company_mgr.jsp" class="list-group-item">공고 현황</a>
           	  <a href="#" class="list-group-item active">공고 등록</a>
			</div>
        </div>
        
        <div class="col-sm-8 blog-main">

          <div class="blog-post">
            <h2 class="blog-post-title">공고 등록하기</h2>
		 <%
		if (session_id!=null) {  
	 %>  
			<form method="post" action="./notice_add.jsp" style="padding: 15px; margin:0 auto;">
				<input type="text" name="apply_name" class="form-control" placeholder="공고명을 입력해주세요">
				<input type="text" name="apply_start_date" class="form-control" placeholder="공고 시작일을 입력해주세요" >
				<input type="text" name="apply_end_date" class="form-control" placeholder="공고 종료일을 입력해주세요">
				<div id="spec_add">
					<select name="spec_name" class="form-control" >
						    <option value="">자격증 선택</option>
<%
	List<SpecVo> list = ctrl.getSpecList();
	for(int i=0; i<list.size(); i++) {
%>
	
						    <option value="<%=list.get(i).getSpec_code()%>"><%=list.get(i).getSpec_name()%></option>
<%
	}
%>
					</select>
					<input type="text" name="spec_level" class="form-control" placeholder="등급을 입력해주세요" autofocus="">
				</div>
				<textarea name="apply_contents" class="form-control" placeholder="공고 내용을 입력해주세요" ></textarea>
				
			    <button class="btn btn-lg btn-primary btn-block" type="submit">등록하기</button>
			</form>  
			<%
		}
			%>
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
