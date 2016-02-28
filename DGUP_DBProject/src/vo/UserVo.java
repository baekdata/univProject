package vo;

public class UserVo {
	private String email;
	private String address;
	private String passwd;
	private String phone;
	private String name;
	private String cell_phone;
	private String univ_code;
	private String major_code;
	
	private int company_type;
	
	private int flag;
	
	
	
	public int getFlag() {
		return flag;
	}
	public void setFlag(int flag) {
		this.flag = flag;
	}
	
	
	public String getUniv_code() {
		return univ_code;
	}
	public void setUniv_code(String univ_code) {
		this.univ_code = univ_code;
	}
	public String getMajor_code() {
		return major_code;
	}
	public void setMajor_code(String major_code) {
		this.major_code = major_code;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public String getPasswd() {
		return passwd;
	}
	public void setPasswd(String passwd) {
		this.passwd = passwd;
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getCell_phone() {
		return cell_phone;
	}
	public void setCell_phone(String cell_phone) {
		this.cell_phone = cell_phone;
	}
	public int getCompany_type() {
		return company_type;
	}
	public void setCompany_type(int company_type) {
		this.company_type = company_type;
	}
}
