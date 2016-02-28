package vo;
import java.util.Date;

public class ApplyVo {
	private int ApplyIDX;
	private int NoticeIDX;
	private Date ApplyDate;
	private int Status;
	private String Email;
	
	private String seeker_name;
	private String resume;
	
	private String applyName;
	private String companyName;
	
	
	
	
	public String getResume() {
		return resume;
	}
	public void setResume(String resume) {
		this.resume = resume;
	}
	public String getSeeker_name() {
		return seeker_name;
	}
	public void setSeeker_name(String seeker_name) {
		this.seeker_name = seeker_name;
	}
	public String getApplyName() {
		return applyName;
	}
	public void setApplyName(String applyName) {
		this.applyName = applyName;
	}
	public String getCompanyName() {
		return companyName;
	}
	public void setCompanyName(String companyName) {
		this.companyName = companyName;
	}
	public int getApplyIDX() {
		return ApplyIDX;
	}
	public void setApplyIDX(int applyIDX) {
		ApplyIDX = applyIDX;
	}
	public int getNoticeIDX() {
		return NoticeIDX;
	}
	public void setNoticeIDX(int noticeIDX) {
		NoticeIDX = noticeIDX;
	}
	public Date getApplyDate() {
		return ApplyDate;
	}
	public void setApplyDate(Date applyDate) {
		ApplyDate = applyDate;
	}
	public int getStatus() {
		return Status;
	}
	public void setStatus(int status) {
		Status = status;
	}
	public String getEmail() {
		return Email;
	}
	public void setEmail(String email) {
		Email = email;
	}
}
