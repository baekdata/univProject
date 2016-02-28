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
            <h2 class="blog-post-title">지원자 현황</h2>
            <table class="table table-bordered">
			  <thead>
			    <tr>
			      <th>#</th>
			      <th>지원자</th>
			      <th>지원서 본문</th>
			      <th>지원 일자</th>
			      <th>진행 상태</th>
			    </tr>
			  </thead>
			  <tbody>
<%
	String idx = request.getParameter("idx");
	List<ApplyVo> list = ctrl.getSeekerlist(Integer.parseInt(idx));
	
	for(int i=0; i<list.size(); i++) {
%>
			    <tr>
			      <th scope="row"><%=i+1 %></th>
			      <td><%=list.get(i).getSeeker_name() %></td>
			      <td><%=list.get(i).getResume() %></td>
			      <td><%=list.get(i).getApplyDate() %></td>
			      <%
			      	if(list.get(i).getStatus()==0) {
			      %>
			      		<td>
			      			<button type="button" class="btn btn-success bb" type1="1" val="<%= list.get(i).getApplyIDX()%>">합격</button>
			      			<button type="button" class="btn btn-danger bb" type1="2" val="<%= list.get(i).getApplyIDX()%>">불합격</button>
			      		</td>
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
			$(".btn.bb").click(function() {
				var f = document.createElement('form');
				objs = document.createElement('input');
				objs.setAttribute('type', 'hidden');
			    objs.setAttribute('name', 'idx');
				objs.setAttribute('value', '<%=idx%>');
				
				objs2 = document.createElement('input');
				objs2.setAttribute('type', 'hidden');
			    objs2.setAttribute('name', 'seeker');
				objs2.setAttribute('value', $(this).attr("val"));
				
				
				objs3 = document.createElement('input');
				objs3.setAttribute('type', 'hidden');
			    objs3.setAttribute('name', 'type1');
				objs3.setAttribute('value', $(this).attr("type1"));
				
				f.appendChild(objs);
				f.appendChild(objs2);
				f.appendChild(objs3);
				f.setAttribute('method', 'post');
				f.setAttribute('action', 'apply_proc.jsp');
				document.body.appendChild(f);
				f.submit();
			});
		});
	</script>
  </body>
</html>
