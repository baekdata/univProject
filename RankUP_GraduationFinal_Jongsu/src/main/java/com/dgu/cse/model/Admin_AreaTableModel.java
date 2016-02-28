package com.dgu.cse.model;

public class Admin_AreaTableModel {
	 private int id;
	 private String location;
	 private String restaurant;
	 private int total_cnt;
	 private String update_date;
	public int getId() {
		return id;
	}
	public void id(int admin_id) {
		this.id = admin_id;
	}
	public String getUpdate_date() {
		return update_date;
	}
	public void setUpdate_date(String update_date) {
		this.update_date = update_date;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public String getRestaurant() {
		return restaurant;
	}
	public void setRestaurant(String restaurant) {
		this.restaurant = restaurant;
	}
	public int getTotal_cnt() {
		return total_cnt;
	}
	public void setTotal_cnt(int total_cnt) {
		this.total_cnt = total_cnt;
	}
	 
}
