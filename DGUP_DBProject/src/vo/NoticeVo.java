package vo;

import java.util.Date;

public class NoticeVo {
	private String company_name;
	private String notice_name;
	private int notice_idx;
	
	private Date start_date;
	private Date end_date;
	
	private String type_of_bussiness;
	
	private String notice_contents;
	
	

	public String getNotice_contents() {
		return notice_contents;
	}

	public void setNotice_contents(String notice_contents) {
		this.notice_contents = notice_contents;
	}

	public String getCompany_name() {
		return company_name;
	}

	public void setCompany_name(String company_name) {
		this.company_name = company_name;
	}

	public String getNotice_name() {
		return notice_name;
	}

	public void setNotice_name(String notice_name) {
		this.notice_name = notice_name;
	}

	public int getNotice_idx() {
		return notice_idx;
	}

	public void setNotice_idx(int notice_idx) {
		this.notice_idx = notice_idx;
	}

	public Date getStart_date() {
		return start_date;
	}

	public void setStart_date(Date start_date) {
		this.start_date = start_date;
	}

	public Date getEnd_date() {
		return end_date;
	}

	public void setEnd_date(Date end_date) {
		this.end_date = end_date;
	}

	public String getType_of_bussiness() {
		return type_of_bussiness;
	}

	public void setType_of_bussiness(String type_of_bussiness) {
		this.type_of_bussiness = type_of_bussiness;
	}
	
	
	
}
