package com.dgu.cse.controller;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.dgu.cse.model.AdminModel;
import com.dgu.cse.service.LoginService;

@Controller
public class AdminController {
	@Autowired 
	LoginService loginService;
	
	@RequestMapping(value = "/adminLogin", method = RequestMethod.GET)
	public String adminLogin(HttpServletRequest request, Model model) {
		return "adminViews/adminLogin";
	}
	@RequestMapping(value = "/login", method = RequestMethod.POST)
	public String loginSucc(HttpServletRequest request, Model model, AdminModel adminModel) {
		if(loginService.isValidateAdmin(adminModel)) return "adminViews/popup/loginSucc";
		else return "adminViews/popup/loginFail";
	}
	@RequestMapping(value = "/adminDashboard")
	public String adminDashboard(HttpServletRequest request, Model model) {
		return "adminViews/adminDashboard";
	}
	@RequestMapping(value = "/ready", method = RequestMethod.POST)
	public String adminReady(HttpServletRequest request, Model model) {
		return "adminViews/adminReady";
	}
	@RequestMapping(value = "/crawlDone", method = RequestMethod.POST)
	public String crawlDone(HttpServletRequest request, Model model) {
		return "adminViews/popup/crawlDone";
	}
	
}
