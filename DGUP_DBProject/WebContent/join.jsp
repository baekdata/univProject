<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="java.util.*, vo.*"%>
<jsp:useBean id="ctrl" class="controller.Controller" scope="page"/>
<!DOCTYPE html>
<html lang="en">
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
	  
	    <h2 class="form-signin-heading">회원가입</h2>
	    
		<div role="tabpanel">

			  <!-- Nav tabs -->
			  <ul class="nav nav-tabs" role="tablist">
			    <li role="presentation" class="active"><a href="#person" aria-controls="person" role="tab" data-toggle="tab">개인회원</a></li>
			    <li role="presentation"><a href="#company" aria-controls="company" role="tab" data-toggle="tab">기업회원</a></li>
			    
			  </ul>
			
			  <!-- Tab panes -->
			  <div class="tab-content">
			    <div role="tabpanel" class="tab-pane active" id="person">
				    <form class="form-signin"  method="post" action="./login_verify.jsp" style="max-width: 700px;padding: 15px;margin: 0 auto;">
						<label for="inputEmail" class="sr-only">아이디</label>
					    <input type="email" id="inputEmail" class="form-control" placeholder="아이디를 입력해주세요" required="" autofocus="">
					    <label for="inputPassword" class="sr-only">비밀번호</label>
					    <input type="password" id="inputPassword" class="form-control" placeholder="비밀번호를 입력해주세요" required="">
					    <input type="text" id="inputName" class="form-control" placeholder="이름을 입력해주세요" autofocus="">
					    <input type="text" id="inputAddress" class="form-control" placeholder="주소를 입력해주세요" autofocus="">
					    <input type="text" id="inputPhone" class="form-control" placeholder="전화번호를 입력해주세요" autofocus="">

					    <select id="inputUnivname" class="form-control" >
						    <option value="">대학교 선택</option>
<%
	List<UnivVo> list = ctrl.getUnivList();
	for(int i=0; i<list.size(); i++) {
%>
	
						    <option value="<%=list.get(i).getUniv_code()%>"><%=list.get(i).getUniv_name()%></option>
<%
	}
%>
						</select>
						<select id="inputDepartname" class="form-control" disable >
						    <option value="">학과 선택</option>
						</select>
					    
					    <button class="btn btn-lg btn-primary btn-block" type="submit">가입하기</button>
					  </form>  
			    </div>
			    <div role="tabpanel" class="tab-pane" id="company">
				    <form class="form-signin"  method="post" action="./login_verify.jsp" style="max-width: 700px;padding: 15px;margin: 0 auto;">
					    <label for="inputEmail" class="sr-only">아이디</label>
					    <input type="email" id="inputEmail" class="form-control" placeholder="아이디를 입력해주세요" required="" autofocus="">
					    <label for="inputPassword" class="sr-only">비밀번호</label>
					    <input type="password" id="inputPassword" class="form-control" placeholder="비밀번호를 입력해주세요" required="">
					    <input type="text" id="inputName" class="form-control" placeholder="회사이름을 입력해주세요" autofocus="">
					    <input type="text" id="inputAddress" class="form-control" placeholder="주소를 입력해주세요" autofocus="">
					    <input type="text" id="inputPhone" class="form-control" placeholder="전화번호를 입력해주세요" autofocus="">
					    <select id="inputUnivname" class="form-control" >
						    <option value="">업종 선택</option>
						    <option value="opic">IT</option>
						    <option value="toeic">금융</option>
						    <option value="정보처리">출판</option>
						</select>
					    
					    <button class="btn btn-lg btn-primary btn-block" type="submit">가입하기</button>
					  </form>  
			    </div>
			  </div>
			
			</div>
			
			
	    
	
	</div>
	
	
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






