<?xml version="1.0" encoding="UTF-8" ?>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<script>

$( document ).ready(function() {
	console.log("loginSucc");
	alert("로그인에 성공하였습니다. 잠시만 기다려주세요.");
	$("#goAdmin").prop("href", "/cse/adminDashboard");
	$("#goAdmin").trigger("click");
});
</script>
<a href="#" id="goAdmin" onclick="window.open(this.href,'_self')"></a>
