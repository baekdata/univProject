package com.dgu.cse.dao;

import java.util.List;

import org.mybatis.spring.SqlSessionTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import com.dgu.cse.model.Admin_AreaTableModel;
import com.dgu.cse.model.SearchInfoModel;

@Repository
public class AdminDao {
	
	@Autowired
	SqlSessionTemplate sqlSession;
	
	public List<Admin_AreaTableModel> getSeoul() {
		return sqlSession.selectList("AdminMapper.getSeoul");
	}
	public int insertCrawledData(Admin_AreaTableModel searchInfoData){
		int result = sqlSession.insert("CrawlMapper.test", searchInfoData);
		sqlSession.commit();
		sqlSession.close();
		return result;
	}
	public List<Admin_AreaTableModel> getBusan() {
		return sqlSession.selectList("AdminMapper.getBusan");
	}
	public List<Admin_AreaTableModel> getJeju() {
		return sqlSession.selectList("AdminMapper.getJeju");
	}
	public List<Admin_AreaTableModel> getGyeongGi() {
		return sqlSession.selectList("AdminMapper.getGyeongGi");
	}
	public List<Admin_AreaTableModel> getGangwon() {
		return sqlSession.selectList("AdminMapper.getGangwon");
	}
	public List<Admin_AreaTableModel> getGyeongsang() {
		return sqlSession.selectList("AdminMapper.getGyeongsang");
	}
	public List<Admin_AreaTableModel> getJeonra() {
		return sqlSession.selectList("AdminMapper.getJeonra");
	}
	public List<Admin_AreaTableModel> getChoongChung() {
		return sqlSession.selectList("AdminMapper.getChoongChung");
	}
}
