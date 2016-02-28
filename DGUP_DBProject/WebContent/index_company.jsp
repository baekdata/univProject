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
	  <div class="jumbotron">
	     <div class="container">
	       <h1>지금 DGUP에 가입하세요!</h1>
	       <p>지금 가입하시면 자신의 스펙에 맞는 회사의 채용 공고만 볼 수 있습니다.</p>
	       <p>또한 자신의 스펙을 한눈에 정리되어진 결과를 볼 수 있습니다.</p> 
	     </div> 
	   </div>
	<%
		} else {
	%>  
	  <div class="jumbotron">
	     <div class="container">
	       <p>당신에 스펙에 맞는 회사의 채용 공고들을 확인해보세요.</p>
	     </div> 
	   </div>	
	<%
		}
	%>
    <div class="container">
      <!-- Example row of columns -->
      <div class="bs-callout bs-callout-info" id="callout-type-b-i-elems" style="padding: 13px;margin: 20px 0;border: 1px solid #eee;border-left-width: 5px;border-radius: 3px;border-left-color: #1b809e;">
	  	<h4 id="alternate-elements" >현재 진행중인 모집 공고</h4>
	  </div>
      <div class="row">
<%
	List<NoticeVo> list = ctrl.now_notice(session_id);
	List<NoticeVo> list2 = ctrl.next_date_notice(session_id);
	List<NoticeVo> list3 = ctrl.out_date_notice(session_id);
	
	for(int i=0; i<list.size(); i++) {
%>

        <div class="col-md-4">
          <h3>[<%=list.get(i).getCompany_name() %>]</h3>
          <p>공고명:<%= list.get(i).getNotice_name() %></p>
          <p>모집기간 : <%=list.get(i).getStart_date() %>~<%=list.get(i).getEnd_date() %></p>
          <p><a class="btn btn-default" href="#" role="button" type="0" val="<%=list.get(i).getNotice_idx()%>">자세히 보기 &raquo;</a></p>
        </div>
<%
	}
%>
      </div>

	  <div class="bs-callout bs-callout-info" id="callout-type-b-i-elems" style="padding: 13px;margin: 70px 0px 20px 0px;border: 1px solid #eee;border-left-width: 5px;border-radius: 3px;border-left-color: red;">
	  	<h4 id="alternate-elements" >접수 예정 모집 공고</h4>
	  </div>
      <div class="row">
<%
	for(int i=0; i<list2.size(); i++) {
%>

        <div class="col-md-4">
          <h3>[<%=list2.get(i).getCompany_name() %>]</h3>
          <p>공고명:<%= list2.get(i).getNotice_name() %></p>
          <p>모집기간 : <%=list2.get(i).getStart_date() %>~<%=list2.get(i).getEnd_date() %></p>
          <p><a class="btn btn-default" href="#" role="button"  type="1"  val="<%=list2.get(i).getNotice_idx()%>">자세히 보기 &raquo;</a></p>
        </div>
<%
	}
%>
      </div>
      
      
      <div class="bs-callout bs-callout-info" id="callout-type-b-i-elems" style="padding: 13px;margin: 70px 0px 20px 0px;border: 1px solid #eee;border-left-width: 5px;border-radius: 3px;border-left-color: black;">
	  	<h4 id="alternate-elements" >마감되어진 모집 공고</h4>
	  </div>
      <div class="row">
<%
	for(int i=0; i<list3.size(); i++) {
%>

        <div class="col-md-4">
          <h3>[<%=list3.get(i).getCompany_name() %>]</h3>
          <p>공고명:<%= list3.get(i).getNotice_name() %></p>
          <p>모집기간 : <%=list3.get(i).getStart_date() %>~<%=list3.get(i).getEnd_date() %></p>
          <p><a class="btn btn-default" href="#" role="button"  type="2" val="<%=list3.get(i).getNotice_idx()%>">자세히 보기 &raquo;</a></p>
        </div>
<%
	}
%>
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
			$("a.btn").click(function() {
				var f = document.createElement('form');
				objs = document.createElement('input');
				objs.setAttribute('type', 'hidden');
			    objs.setAttribute('name', 'idx');
				objs.setAttribute('value', $(this).attr("val"));
				
				objs2 = document.createElement('input');
				objs2.setAttribute('type', 'hidden');
			    objs2.setAttribute('name', 'type');
				objs2.setAttribute('value', $(this).attr("type"));
				
				f.appendChild(objs);
				f.appendChild(objs2);
				f.setAttribute('method', 'post');
				f.setAttribute('action', 'notice_detail.jsp');
				document.body.appendChild(f);
				f.submit();
			});
		});
	</script>
  </body>
</html>
