package com.dgu.cse.controller;

import java.util.List;
import java.util.Locale;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.dgu.cse.model.Admin_AreaTableModel;
import com.dgu.cse.service.AdminAreaTableService;
import com.dgu.cse.service.CrawlService;

@Controller
public class AreaController {
	@Autowired
	AdminAreaTableService adminAreaTableService;
	@Autowired
	CrawlService crawlService;
	
	@RequestMapping(value = "/seoul", method = RequestMethod.GET)
	public String seoul(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Seoul");
		model.addAttribute("areaDataList", adminAreaTableService.getSeoul());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachSeoul", method = RequestMethod.GET)
	public String crawlEachSeoul(HttpServletRequest request, Model model, String index,Locale locale) throws Exception {
		List<Admin_AreaTableModel> temp = adminAreaTableService.getQueryDataForSeoul();
		int position = Integer.parseInt(index);
		//crawlService.saveCrawledData(temp.get(position-1), locale);
		adminAreaTableService.testinsert(temp.get(position-1));
		
		return "adminViews/popup/crawlDone";
	}
	
	
	
	@RequestMapping(value = "/busan", method = RequestMethod.GET)
	public String busan(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Busan");
		model.addAttribute("areaDataList", adminAreaTableService.getBusan());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachBusan", method = RequestMethod.GET)
	public String crawlEachBusan(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForBusan());
		
		return "adminViews/popup/crawlDone";
	}
	
	
	@RequestMapping(value = "/jeju", method = RequestMethod.GET)
	public String jeju(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Jeju");
		model.addAttribute("areaDataList", adminAreaTableService.getJeju());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachJeju", method = RequestMethod.GET)
	public String crawlEachJeju(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForJeju());

		return "adminViews/popup/crawlDone";
	}
	@RequestMapping(value = "/gyeonggi", method = RequestMethod.GET)
	public String gyeonggi(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Gyeonggi");
		model.addAttribute("areaDataList", adminAreaTableService.getGyeongGi());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachGyeonggi", method = RequestMethod.GET)
	public String crawlEachGyeonggi(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForGyeongGi());

		return "adminViews/popup/crawlDone";
	}
	@RequestMapping(value = "/gangwon", method = RequestMethod.GET)
	public String Gangwon(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Gangwon");
		model.addAttribute("areaDataList", adminAreaTableService.getGangwon());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachGangwon", method = RequestMethod.GET)
	public String crawlEachGangwon(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForGangwon());

		return "adminViews/popup/crawlDone";
	}
	@RequestMapping(value = "/gyeongsang", method = RequestMethod.GET)
	public String Gyeongsang(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Gyeongsang");
		model.addAttribute("areaDataList", adminAreaTableService.getGyeongsang());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachGyeongsang", method = RequestMethod.GET)
	public String crawlEachGyeongsang(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForGyeongsang());

		return "adminViews/popup/crawlDone";
	}
	@RequestMapping(value = "/jeonra", method = RequestMethod.GET)
	public String Jeonra(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Jeonra");
		model.addAttribute("areaDataList", adminAreaTableService.getJeonra());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachJeonra", method = RequestMethod.GET)
	public String crawlEachJeonra(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForJeonra());

		return "adminViews/popup/crawlDone";
	}
	@RequestMapping(value = "/choongchung", method = RequestMethod.GET)
	public String Choongchung(HttpServletRequest request, Model model) {
		model.addAttribute("areaName", "Choongchung");
		model.addAttribute("areaDataList", adminAreaTableService.getChoongChung());
		return "adminViews/areaTable";
	}
	@RequestMapping(value = "/crawlEachChoongchung", method = RequestMethod.GET)
	public String crawlEachChoongchung(HttpServletRequest request, Model model, String index) {
		model.addAttribute("areaDataQueryList", adminAreaTableService.getQueryDataForChoongChung());

		return "adminViews/popup/crawlDone";
	}
}
