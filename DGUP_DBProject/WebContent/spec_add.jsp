<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>

<%
	String idx = request.getParameter("idx");
//	int type = Integer.parseInt(request.getParameter("type"));
	//SpecVo list = ctrl.all_notice(id)(idx);
	//int type = Integer.parseInt(request.getParameter("type"));
	//NoticeVo list = ctrl.noticeDetail(idx);
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
			  <a href="./spec.jsp" class="list-group-item">스팩 현황</a>
           	  <a href="#" class="list-group-item  active">스팩 등록</a>
           	  <a href="./spec_apply.jsp" class="list-group-item">지원 현황</a>
			</div>
        </div>
        
        <div class="col-sm-8 blog-main">

          <div class="blog-post">
            <h2 class="blog-post-title">스팩 등록하기</h2>
				

			<div role="tabpanel">

			  <!-- Nav tabs -->
			  <ul class="nav nav-tabs" role="tablist">
			    <li role="presentation" class="active"><a href="#cert" aria-controls="cert" role="tab" data-toggle="tab">자격증</a></li>
			    
			  </ul>
			  <!-- Tab panes -->
			  <div class="tab-content">
			    <div role="tabpanel" class="tab-pane active" id="cert">
				    <form method="post" action="./spec_add_proc.jsp" style="padding: 15px;margin: 0 auto;"> 
						<select id="specName" class="form-control">
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
						<textarea name="spec_level" class="form-control" placeholder="등급을 입력해주세요" style="width: 98.9%;"></textarea>
					    <button class="btn btn-lg btn-primary btn-block" type="submit">등록하기</button>
					</form>  
			    </div>
			    
			  </div>
			</div>
			         
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
	</script>
  </body>
</html>
