package com.dgu.cse.dao;

import org.mybatis.spring.SqlSessionTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import com.dgu.cse.model.SearchInfoModel;

@Repository
public class CrawlDao {
	
	@Autowired
	SqlSessionTemplate sqlSession;
	
	public int insertCrawledData(SearchInfoModel searchInfoData){
		int result = sqlSession.insert("CrawlMapper.saveCrawledData", searchInfoData);
		sqlSession.commit();
		sqlSession.close();
		return result;
	}

}
