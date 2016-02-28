package com.dgu.cse.service;

import org.springframework.stereotype.Service;

import com.dgu.cse.model.AdminModel;

@Service 
public class LoginService {
	
	public boolean isValidateAdmin(AdminModel adminModel){
		if(adminModel.getUsername().equals("kelly")&&adminModel.getPassword().equals("pwpw")) return true;
		return false;		
	}

}
