package com.dgu.cse.service;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Locale;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.dgu.cse.dao.CrawlDao;
import com.dgu.cse.model.Admin_AreaTableModel;
import com.dgu.cse.model.RecentModificationInfo;
import com.dgu.cse.model.SearchInfoModel;

@Service
public class CrawlService {
	@Autowired
	CrawlDao crawlDao;
	
	private ArrayList<SearchInfoModel> list;
	private int totalCnt;
	
	public void saveCrawledData(Admin_AreaTableModel areaInfo, Locale locale) throws Exception{
		RecentModificationInfo recentModificationInfo = new RecentModificationInfo();
		
		this.getBlogInfo(areaInfo);
		for(int i=0; i<list.size(); ++i){
			System.out.println(crawlDao.insertCrawledData(list.get(i)));
		}
		recentModificationInfo.setTotalCount(totalCnt);
		recentModificationInfo.setUpdateDate(locale.toString());
		recentModificationInfo.setRestaurant(areaInfo.getRestaurant());
	}
	// 블로그 정보 Crawl
	private void getBlogInfo(Admin_AreaTableModel areaInfo) throws Exception {
		
		this.list = new ArrayList<SearchInfoModel>();
		this.totalCnt = 0;
		
		final String USER_AGENT = "Mozilla/5.0";
		
		String keyword = areaInfo.getLocation() + " " + areaInfo.getRestaurant();
		keyword = URLEncoder.encode(keyword, "UTF-8");
		for(int currentPageNumber=1; currentPageNumber< 501; ++currentPageNumber){
			String url = "https://apis.daum.net/search/blog?apikey=a314a46e01936f1c37a2b0847c40d538&q=" + keyword + "&output=xml&pageno=" + currentPageNumber + "&result=20&sort=accu";
			URL obj = new URL(url);
			HttpURLConnection con = (HttpURLConnection) obj.openConnection();

			// optional default is GET
			con.setRequestMethod("GET");

			//add request header
			con.setRequestProperty("User-Agent", USER_AGENT);

			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream(), "UTF-8"));
			String inputLine;
			
			int flag = 0;
			String link = null;
			int category = 0;
			String blog_name = null;
			int post_id = 0;
			
			int node_flag = 0; // 0인 경우에만 객체 생성
			SearchInfoModel searchInfo = new SearchInfoModel();

			// title, description, link
			while((inputLine = in.readLine()) != null) {
				if(node_flag == 0) {
					searchInfo = new SearchInfoModel();
					node_flag = 1;
				}
				
				if(inputLine.indexOf("<totalCount>") != -1) {
					String temp = inputLine;
					temp = temp.replace("<totalCount>", "");
					temp = temp.replace("</totalCount>", "");
					
					totalCnt = Integer.parseInt(temp);
					flag = 1;
				} else if((inputLine.indexOf("<link>") != -1) && (flag == 1)) {
					String temp = inputLine;
					temp = temp.replace("<link>", "");
					temp = temp.replace("</link>", "");
					
					link = temp;
					
					if(inputLine.indexOf("blog.daum.net") != -1) { // Daum Blog
						category = 1;
						temp = temp.replace("http://blog.daum.net/", "");
						
						blog_name = temp.substring(0, temp.indexOf('/'));
						post_id = Integer.parseInt(temp.substring(temp.indexOf('/') + 1, temp.length()));
					} else if(inputLine.indexOf("tistory.com") != -1) { // Tistory Blog
						category = 2;
						temp = temp.replace("http://", "");
						temp = temp.replace(".tistory.com", "");
						
						blog_name = temp.substring(0, temp.indexOf('/'));
						post_id = Integer.parseInt(temp.substring(temp.indexOf('/') + 1, temp.length()));
						
					} else { // etc
						category = 3;
					}
					
					searchInfo.setId(areaInfo.getId());
					searchInfo.set_link(link);
					searchInfo.set_category(category);
					searchInfo.set_blogName(blog_name);
					searchInfo.set_postId(post_id);
					
					int add_flag = 1; // 1인 경우에만 리스트에 추가(0이면 이미 존재)
					
					for(int i = 0; i < list.size(); i++) {
						if(list.get(i).get_link().equals(link)) {
							add_flag = 0;
							break;
						}
					}
					
					if(add_flag == 1) {
						list.add(searchInfo);
					}
					
					blog_name = null;
					post_id = 0;
					node_flag = 0;
				} else if((inputLine.indexOf("<description>") != -1) && (flag == 1)) {
					String temp = inputLine;
					temp = temp.replace("<description>", "");
					temp = temp.replace("</description>", "");
					temp = temp.replace(";", "");
					temp = temp.replace("&lt", "");
					temp = temp.replace("/b&gt", "");
					temp = temp.replace("b&gt", "");
					
					searchInfo.set_description(temp);
				}
			}
			
			in.close();
		}
		
	}
}