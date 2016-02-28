package com.dgu.cse.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.dgu.cse.dao.AdminDao;
import com.dgu.cse.model.Admin_AreaTableModel;

@Service 
public class AdminAreaTableService {
	
	@Autowired
	AdminDao adminDao;
	public List<Admin_AreaTableModel> getSeoul() {
		return adminDao.getSeoul();
	}
	public int testinsert(Admin_AreaTableModel searchInfoData){
		return adminDao.insertCrawledData(searchInfoData);
	}
	public List<Admin_AreaTableModel> getQueryDataForSeoul() {
		List<Admin_AreaTableModel> temp = adminDao.getSeoul();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
	}
	public List<Admin_AreaTableModel> getBusan() {
		return adminDao.getBusan();
	}
	public List<Admin_AreaTableModel> getQueryDataForBusan() {
		
		List<Admin_AreaTableModel> temp = adminDao.getBusan();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
	}
	public List<Admin_AreaTableModel> getJeju() {
		return adminDao.getJeju();
	}
	public List<Admin_AreaTableModel> getQueryDataForJeju() {
		
		List<Admin_AreaTableModel> temp = adminDao.getJeju();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
	}
	public List<Admin_AreaTableModel> getGyeongGi() {
		return adminDao.getGyeongGi();
	}
	public List<Admin_AreaTableModel> getQueryDataForGyeongGi() {
		
		List<Admin_AreaTableModel> temp = adminDao.getGyeongGi();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
				
	}
	public List<Admin_AreaTableModel> getGangwon() {
		return adminDao.getGangwon();
	}
	public List<Admin_AreaTableModel> getQueryDataForGangwon() {
		
		List<Admin_AreaTableModel> temp = adminDao.getGangwon();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
		
	}
	public List<Admin_AreaTableModel> getGyeongsang() {
		return adminDao.getGyeongsang();
	}
	public List<Admin_AreaTableModel> getQueryDataForGyeongsang() {
		
		List<Admin_AreaTableModel> temp = adminDao.getGyeongsang();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
		
	}
	public List<Admin_AreaTableModel> getJeonra() {
		return adminDao.getJeonra();
	}
	public List<Admin_AreaTableModel> getQueryDataForJeonra() {
		
		List<Admin_AreaTableModel> temp = adminDao.getJeonra();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
		
	}
	public List<Admin_AreaTableModel> getChoongChung() {
		return adminDao.getChoongChung();
	}
	public List<Admin_AreaTableModel> getQueryDataForChoongChung() {
		
		List<Admin_AreaTableModel> temp = adminDao.getChoongChung();

		for(int i = 0; i < temp.size(); i++) {
			String location = temp.get(i).getLocation();
			
			int index = location.indexOf(" ");
			location = location.replace(location.substring(0, index + 1), "");
			index = location.indexOf(" ");
			location = location.replace(location.substring(index, location.length()), "");
			
			temp.get(i).setLocation(location);
		}
		
		return temp;
		
		
	}
}
