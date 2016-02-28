<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>

<%
	String idx = request.getParameter("idx");
	String typeString = request.getParameter("type");
	int TYPE = Integer.parseInt(typeString);
	
	/* String subject=request.getParameter("type");
	//String type2 = request.getParameter("type");
	//int type=0;
	//if(type2 !=null){
	//	type = Integer.parseInt(type2);
	//}else{
	//	type =0;
	//}
	*/
	NoticeVo list = ctrl.noticeDetail(idx);
	List<FaqVo> list2 = ctrl.get_questionList(idx);
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
	  <center>
	  	  
	  <%
	  	if(TYPE==0) {
	  		
	  %>
     	<form method="post" action="./notice_apply.jsp" style="max-width: 700px;padding: 15px;margin: 0 auto;">
     		<input type="hidden" name="noticeIDX" value="<%=idx%>">
     		<input type="hidden" name="type" value="<%=TYPE%>">
     		<button type="submit" class="btn btn-success">지원서 작성</button>
     	</form>`
     <%
	  	} else if(TYPE>0) {
	 %>
	  		<button type="button" class="btn btn-danger">모집기간이 아닙니다</button>
	 <%
	  	}
     %>
     </center>
     <br>
     <br>
     
     
     <p class="bg-primary"  style="padding: 15px;font-size: 17px;font-weight: bold;">문의하기</p>
     <%
		if (session_id!=null && session_flag == 1) {  
	 %>  
     <form name = "question" action="./notice_faq_question_proc.jsp" method="post"> 
     	  <input type="hidden" name="notice_idx" value="<%=idx%>">
     		<input type="hidden" name="type" value="<%=TYPE%>">
		  <div class="row" style="padding-left:17px;">
	     		<textarea name="faq_contents" class="form-control" placeholder="질문을 입력해주세요" style="width: 98.9%;"></textarea>
	      </div>

	      <center><button type="submit" class="btn btn-info" style="margin-top: 15px;">질문 등록하기</button></center>
		  <br>
	      <br>
      </form>
      <%
		}  
	 %> 
     <div class="row" style="padding-left:17px;">
<% 
	for(int i=0; i<list2.size(); i++) {
		FaqVo answer = ctrl.get_answerList(list2.get(i).getQuestionIdx());
%>
     	<div style="width: 98.7%;">
          <p class="bg-danger"  style="padding: 15px;font-size: 12px">
          	    Q.  <%=list2.get(i).getQuestionContents() %>
              <% if(session_flag == 2) {%>
              <%
              	if(answer == null) {
              %>
              	<a class="btn btn-default" role="button">답변 &raquo;</a>
              <%
              	}
              %>
              <div class="answer" style="display:none;">
              	<form method="post" action="./notice_faq_answer_proc.jsp" >
              		<input type="hidden" name="notice_idx" value="<%=idx%>">
              		<input type="hidden" name="question_idx" value="<%=list2.get(i).getQuestionIdx()%>">
              		<input type="hidden" name="type" value="<%=TYPE%>">
              		<textarea name="faq_contents" class="form-control" placeholder="답변을 입력해주세요" style="width: 98.9%;margin-bottom: 15px;"></textarea>
              		<center><button type="submit" class="btn btn-info" style="margin-bottom: 10px;">답변 등록하기</button></center>
              	</form>
              </div>
              <% } %>
              
              <%
              	if(answer != null) {
              %>
		          <p class="bg-success"  style="padding: 15px;font-size: 12px">
		          		A. <%=answer.getAnswerContents() %>
		          </p>
		      <%
              	}
		      %>
	       </p>
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
			$("#login_btn").click(function() {//@@@@ + 추가
				location.href="./login.jsp";
			});
			$("#signin_btn").click(function() {
				location.href="./join.jsp";
			});
			$("#logout_btn").click(function() {
				location.href="./logout.jsp";
			});	
			$("a.btn").click(function() {
				console.log($(this).parent().parent().find(".answer"));
				$(this).parent().parent().find(".answer").show();
			});
		});
	</script>
  </body>
</html>
