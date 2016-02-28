<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
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
	  <form class="form-signin"  method="post" action="./login_verify.jsp" style="max-width: 330px;padding: 15px;margin: 0 auto;">
	    <h2 class="form-signin-heading">로그인</h2>
	    <label for="inputEmail" class="sr-only">아이디</label>
	    <input type="email" id="inputEmail" name="inputEmail" class="form-control" placeholder="아이디를 입력해주세요" required="" autofocus="">
	    <label for="inputPassword" class="sr-only">비밀번호</label>
	    <input type="password" id="inputPassword" name="inputPassword" class="form-control" placeholder="비밀번호를 입력해주세요" required="">
	    <div class="checkbox">
	      	<label class="radio-inline">
			  <input type="radio" name="inlineRadioOptions" id="inlineRadio1" value="1" checked> 개인회원
			</label>
			<label class="radio-in
			line">
			  <input type="radio" name="inlineRadioOptions" id="inlineRadio2" value="2"> 기업회원
			</label>
	    </div>
	    <button class="btn btn-lg btn-primary btn-block" type="submit">로그인</button>
	  </form>
	
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






