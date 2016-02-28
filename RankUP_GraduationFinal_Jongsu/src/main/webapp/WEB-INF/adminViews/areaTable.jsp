<?xml version="1.0" encoding="UTF-8" ?>
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<div class="container">
	<div class="row">
	<h2 style="float:center">${areaName}</h2>
	<HR/>
		<div class="col-lg-10 col-lg-offset-1 text-center">
			<div class="table-responsive">
				<table class="table table-bordered table-hover table-striped">
					<thead>
						<tr>
							<th>#</th>
							<th>Location</th>
							<th>Restaurant name</th>
						    <th>total Count</th>
							<th>Last modified date</th>
							<th></th>
						</tr>
					</thead>
					<tbody>
						<c:forEach var="areaData" items="${areaDataList}" varStatus="index">
							<tr>
								<td>${index.index+1}</td>
								<td>${areaData.location}</td>
								<td>${areaData.restaurant}</td>
								<td>${areaData.total_cnt}</td>
								<td>${areaData.update_date}</td>
								<td><button id ="crawl" onclick="crawl('${index.index+1}')">renew</button></td>
							</tr>
						</c:forEach>
					</tbody>
				</table>
			</div>
		</div>
		<!-- /.col-lg-10 -->
	</div>
	<!-- /.row -->
</div>
<!-- /.container -->
<div id = "popup" style="float:center">renewing process requires approximately 2~3mins! please wait until the pop-up for completion</div>

<script type="text/javascript">
function crawl(index) {
	var area = "${areaName}";
	areaUrl = "/cse/crawlEach"+area;
	$.get( areaUrl, {index:index}).done(function(html) {
		console.log("crawling!!");
		$("#popup").html(html);
	});
}


</script>