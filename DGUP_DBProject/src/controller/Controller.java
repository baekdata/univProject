package controller;

import java.sql.* ;
import java.util.*;
import java.sql.Date;

import db.* ;
import vo.* ;


public class Controller {
	private DBConnectionPool connector;

	public Controller() {
		connector = DBConnectionPool.getInstance();
	}
	
	
	public List<ApplyVo> getApplyList(String id) {
		
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<ApplyVo> list = new ArrayList<ApplyVo>();
		try {

			conn = connector.getConn();
			stmt = conn.prepareStatement("select a.applydate, o.companyname, n.noticename, a.status from apply a, employer_member o, emp_notice n where a.noticeidx=n.noticeidx and n.email=o.email and a.email=?");
			
			int idx =1;
			stmt.setString(idx++, id);
			
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠

				ApplyVo apply = new ApplyVo();
				
				apply.setApplyDate(rs.getDate("APPLYDATE"));
				apply.setCompanyName(rs.getString("COMPANYNAME"));
				apply.setApplyName(rs.getString("NOTICENAME"));
				apply.setStatus(rs.getInt("STATUS"));
				
				list.add(apply);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		
		return list;
	}
	
	public List<ApplyVo> getSeekerlist(int notice_idx) {
		
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<ApplyVo> list = new ArrayList<ApplyVo>();
		try {

			conn = connector.getConn();
			//stmt = conn.prepareStatement("select u.applyidx, s.firstname, u.resumecontents, a.applydate, a.status from seeker_member s, resume u, apply a, emp_notice e where e.noticeidx=? and a.applyidx=u.applyidx and a.email=s.email");
			stmt = conn.prepareStatement("select distinct u.applyidx, s.firstname, u.resumecontents, a.applydate, a.status from seeker_member s, resume u, apply a, emp_notice e where a.noticeidx=? and a.applyidx=u.applyidx and a.email=s.email");
			
			int idx =1;
			stmt.setInt(idx++, notice_idx);
			
			rs = stmt.executeQuery();
			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠

				ApplyVo apply = new ApplyVo();
				apply.setApplyIDX(rs.getInt("APPLYIDX"));
				apply.setSeeker_name(rs.getString("FIRSTNAME"));
				apply.setResume(rs.getString("RESUMECONTENTS"));
				apply.setApplyDate(rs.getDate("APPLYDATE"));
				apply.setStatus(rs.getInt("STATUS"));
				list.add(apply);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		
		return list;
	}
	
	public List<UnivVo> getUnivList() {
		// DB ?울옙??癰귨옙??占쎌쥙堉?
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<UnivVo> list = new ArrayList<UnivVo>();
		try {

			conn = connector.getConn();
			stmt = conn.prepareStatement("select * from university u");
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠

				UnivVo univ = new UnivVo();
				univ.setUniv_code(rs.getInt("UNIV_CODE"));
				univ.setUniv_name(rs.getString("UNIV_NAME"));
				list.add(univ);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}

	
	public List<SpecVo> getSpecList() {
		Connection conn = null; // DB ?울옙??癰귨옙??占쎌쥙堉?
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<SpecVo> list = new ArrayList<SpecVo>();

		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select * from spec_list");
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				SpecVo spec = new SpecVo();
				spec.setSpec_code(rs.getInt("SPEC_CODE"));
				spec.setSpec_name(rs.getString("SPEC_NAME"));
				list.add(spec);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public List<SpecVo> personSpec_status(String id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<SpecVo> list = new ArrayList<SpecVo>();
		
		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select * from person_spec p, spec_list s where p.spec_code=s.spec_code and p.email=?");
			int idx =1;
			stmt.setString(idx++, id);
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				SpecVo spec = new SpecVo();
				spec.setSpec_name(rs.getString("SPEC_NAME"));
				spec.setScore(rs.getString("SCORE"));
				list.add(spec);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public UserVo LoginProc(String id, String passwd, String userType) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		UserVo user = new UserVo();

		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select a.email, a.flag from all_member a where a.email=? and a.password=? and a.flag=?");
			int idx =1;
			stmt.setString(idx++, id);
			stmt.setString(idx++, passwd);
			stmt.setInt(idx++, Integer.parseInt(userType));
			rs = stmt.executeQuery();
			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠

				user.setEmail(rs.getString("EMAIL"));
				user.setFlag(rs.getInt("FLAG"));
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return user;
	}
	
	public List<NoticeVo> now_notice(String id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		List<NoticeVo> list = new ArrayList<NoticeVo>();

		try {
			conn = connector.getConn();

			if(id==null) {
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate between e.startdate and e.duedate");
			} else {
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from person_spec p, req_spec r, emp_notice e, employer_member o, company_type c, seeker_member q where p.email=? and p.spec_code=r.spec_code and r.noticeidx=e.noticeidx and e.email=o.email and o.type_code=c.type_code and sysdate between e.startdate and e.duedate");
				int idx =1;
				stmt.setString(idx++, id);
			}
			
			
			
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				NoticeVo notice = new NoticeVo();
				
				notice.setCompany_name(rs.getString("COMPANYNAME"));
				notice.setNotice_idx(rs.getInt("NOTICEIDX"));
				notice.setStart_date(rs.getDate("STARTDATE"));
				notice.setEnd_date(rs.getDate("DUEDATE"));
				notice.setNotice_name(rs.getString("NOTICENAME"));
				notice.setType_of_bussiness(rs.getString("TYPEOFBUSINESS"));
				
				
				list.add(notice);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public List<NoticeVo> all_notice(String id) {
		
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		List<NoticeVo> list = new ArrayList<NoticeVo>();
		
		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and e.email=?");
			//stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate between e.startdate and e.duedate");
			int idx=1;
			stmt.setString(idx++, id);
			
			
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				NoticeVo notice = new NoticeVo();
				
				notice.setCompany_name(rs.getString("COMPANYNAME"));
				notice.setNotice_idx(rs.getInt("NOTICEIDX"));
				notice.setStart_date(rs.getDate("STARTDATE"));
				notice.setEnd_date(rs.getDate("DUEDATE"));
				notice.setNotice_name(rs.getString("NOTICENAME"));
				notice.setType_of_bussiness(rs.getString("TYPEOFBUSINESS"));
				
				
				list.add(notice);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public List<NoticeVo> next_date_notice(String id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		List<NoticeVo> list = new ArrayList<NoticeVo>();
		

		try {

			conn = connector.getConn();

			if(id==null) {
				//stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate>e.duedate");
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate<e.startdate");
			} else {
//				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from person_spec p, req_spec r, emp_notice e, employer_member o, company_type c, seeker_member q where p.email=? and p.spec_code=r.spec_code and r.noticeidx=e.noticeidx and e.email=o.email and o.type_code=c.type_code and e.startdate>sysdate");
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from person_spec p, req_spec r, emp_notice e, employer_member o, company_type c, seeker_member q where ?=p.email and p.spec_code=r.spec_code and r.noticeidx=e.noticeidx and e.email=o.email and o.type_code=c.type_code and e.startdate<sysdate;");

				int idx =1;
				stmt.setString(idx++, id);
			}
			
			
			
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				NoticeVo notice = new NoticeVo();
				
				notice.setCompany_name(rs.getString("COMPANYNAME"));
				notice.setNotice_idx(rs.getInt("NOTICEIDX"));
				notice.setStart_date(rs.getDate("STARTDATE"));
				notice.setEnd_date(rs.getDate("DUEDATE"));
				notice.setNotice_name(rs.getString("NOTICENAME"));
				notice.setType_of_bussiness(rs.getString("TYPEOFBUSINESS"));
				
				list.add(notice);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public List<NoticeVo> out_date_notice(String id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		List<NoticeVo> list = new ArrayList<NoticeVo>();

		try {

			conn = connector.getConn();

			if(id==null) {
				//stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate<e.startdate");
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from emp_notice e, employer_member o, company_type c where e.email=o.email and o.type_code=c.type_code and sysdate>e.duedate");

			} else {
				stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from person_spec p, req_spec r, emp_notice e, employer_member o, company_type c, seeker_member q where p.email=? and p.spec_code=r.spec_code and r.noticeidx=e.noticeidx and e.email=o.email and o.type_code=c.type_code and e.duedate<sysdate");
				//stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, e.noticeidx from person_spec p, req_spec r, emp_notice e, employer_member o, company_type c, seeker_member q where ? =p.email and p.spec_code=r.spec_code and r.noticeidx=e.noticeidx and e.email=o.email and o.type_code=c.type_code and e.duedate>sysdate");

				int idx =1;
				stmt.setString(idx++, id);
			}
			
			
			
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				NoticeVo notice = new NoticeVo();
				
				notice.setCompany_name(rs.getString("COMPANYNAME"));
				notice.setNotice_idx(rs.getInt("NOTICEIDX"));
				notice.setStart_date(rs.getDate("STARTDATE"));
				notice.setEnd_date(rs.getDate("DUEDATE"));
				notice.setNotice_name(rs.getString("NOTICENAME"));
				notice.setType_of_bussiness(rs.getString("TYPEOFBUSINESS"));
				
				
				list.add(notice);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	
	public NoticeVo noticeDetail(String notice_idx) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		NoticeVo notice = new NoticeVo();

		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select distinct e.noticename, o.companyname, e.startdate, e.duedate, c.typeofbusiness, t.noticecontents from notice_contents t, emp_notice e, employer_member o, company_type c where e.noticeidx=? and e.email=o.email and t.noticeidx=e.noticeidx and o.type_code=c.type_code");
			int idx =1;
			
			stmt.setInt(idx++, Integer.parseInt(notice_idx));
			
			rs = stmt.executeQuery();
			
			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				notice.setCompany_name(rs.getString("COMPANYNAME"));
				notice.setNotice_idx(Integer.parseInt(notice_idx));
				notice.setStart_date(rs.getDate("STARTDATE"));
				notice.setEnd_date(rs.getDate("DUEDATE"));
				notice.setNotice_name(rs.getString("NOTICENAME"));
				notice.setType_of_bussiness(rs.getString("TYPEOFBUSINESS"));
				notice.setNotice_contents(rs.getString("NOTICECONTENTS"));
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return notice;
	}
	
	public List<FaqVo> get_questionList(String id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		List<FaqVo> list = new ArrayList<FaqVo>();

		try {
			conn = connector.getConn();
			stmt = conn.prepareStatement("select q.quecontent, q.questionidx from question q, emp_notice e where e.noticeidx=q.noticeidx and e.noticeidx=?");
			int idx =1;
			stmt.setInt(idx++, Integer.parseInt(id));
			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				FaqVo faq = new FaqVo();
				
				faq.setQuestionContents(rs.getString("QUECONTENT"));
				faq.setQuestionIdx(rs.getInt("QUESTIONIDX"));
				
				list.add(faq);
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public FaqVo get_answerList(int id) {
		Connection conn = null;
		PreparedStatement stmt = null;
		ResultSet rs = null;
		
		FaqVo list = null;
		
		try {
			conn = connector.getConn();

			stmt = conn.prepareStatement("select a.anscontent from question q, answer a where a.questionidx=? and a.questionidx=q.questionidx");
			int idx =1;
			stmt.setInt(idx++, id);

			rs = stmt.executeQuery();

			while (rs.next()) { // rs占쏙옙筌롳옙?싧쳞?곸뵠占쎈뜃??while?얜챷??占싼딆뒠
				list = new FaqVo();
				list.setAnswerContents(rs.getString("ANSCONTENT"));
			}
			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return list;
	}
	
	public String insertQuestion(String email, int notice_idx, String questionText) {
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;

		try {
			conn = connector.getConn();
			
			String sql = "{call insertQuestion(?,?,?,?)}";
			stmt = conn.prepareCall(sql);
			
			int idx =1;
			stmt.setString(idx++, email);
			stmt.setInt(idx++, notice_idx);
			stmt.setString(idx++, questionText);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
	
	public String insertAnswer(String email, int notice_idx, String questionText) {
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;
		
		try {
			conn = connector.getConn();
			
			String sql = "{call insertAnswer(?,?,?,?)}";
			stmt = conn.prepareCall(sql);
			
			int idx =1;
			stmt.setString(idx++, questionText);
			stmt.setString(idx++, email);
			stmt.setInt(idx++, notice_idx);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);
			stmt.execute();
			result = stmt.getString(idx);
			
			conn.commit();
		} catch(Exception ex) { 
			try {
				
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
	
	public String insertNotice(String email, Date startDate, Date duedate, String noticename, int apply_state, int spec_code, String spec_level, String contents) { //@@
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;

		try {
			conn = connector.getConn();
			
			String sql = "{call insertNotice(?,?,?,?,?,?,?,?,?)}";
			stmt = conn.prepareCall(sql);
			
			int idx =1;
			stmt.setString(idx++, email);
			stmt.setDate(idx++, startDate);
			stmt.setDate(idx++, duedate);
			stmt.setString(idx++, noticename);
			stmt.setInt(idx++, apply_state);
			stmt.setInt(idx++, spec_code);
			stmt.setString(idx++, spec_level);
			stmt.setString(idx++, contents);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
	
	public String insertSpec(int spec_code, String spec_level, String email) { //@@
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;

		try {
			conn = connector.getConn();
			
			String sql = "{call insertSpec(?,?,?,?)}";
			stmt = conn.prepareCall(sql);
			
			int idx =1;
			stmt.setInt(idx++, spec_code);
			stmt.setString(idx++, spec_level);
			stmt.setString(idx++, email);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}

	public String insertApply(int noticeidx, String email, String resume) { //@@
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;
		
		try {
			conn = connector.getConn();
			
			String sql = "{call insertApply(?,?,?,?)}";
			stmt = conn.prepareCall(sql);
			
			int idx =1;
			stmt.setInt(idx++, noticeidx);
			stmt.setString(idx++, email);
			stmt.setString(idx++, resume);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
	
	public String insertResume(int applyidx, String resumecontents) { //@@
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;

		try {
			conn = connector.getConn();
			
			String sql = "{call insertResume(?,?,?)}";
			stmt = conn.prepareCall(sql);	
			
			int idx =1;
			stmt.setInt(idx++, applyidx);
			stmt.setString(idx++, resumecontents);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
	
	public String applyProc(int type, int seeker_idx) { //@@
		Connection conn = null;
		CallableStatement stmt = null;
		String result =null;

		try {
			conn = connector.getConn();
			
			String sql = "{call updateApply(?,?,?)}";
			stmt = conn.prepareCall(sql);	
			
			int idx =1;
			stmt.setInt(idx++, type);
			stmt.setInt(idx++, seeker_idx);
			stmt.registerOutParameter(idx, java.sql.Types.VARCHAR);

			stmt.execute();
			result = stmt.getString(idx); 

			conn.commit();
		} catch(Exception ex) { 
			try {
				conn.rollback();
			} catch(SQLException e){
				e.printStackTrace();
			}
		} finally {
			try {
				if(stmt != null) stmt.close();
			} catch(Exception ex) {
				//ex.printStackTrace();
			}
			connector.freeConn(conn);
		}
		// 野껉퀗?드첎誘れ뱽 ?귐뗪쉘
		return result;
	}
}
