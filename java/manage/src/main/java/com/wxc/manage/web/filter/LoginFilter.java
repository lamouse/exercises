package com.wxc.manage.web.filter;

import java.io.IOException;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.Set;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.wxc.manage.model.User;
import org.apache.log4j.Logger;


public class LoginFilter implements Filter {
	Logger _log = Logger.getLogger(LoginFilter.class);
	/**
	 * 要排除的请求路径(/开头)列表
	 */
	private Set<String> exRoutes = new HashSet<String>();
	
	@Override
	public void destroy() {
		// TODO Auto-generated method stub
	}

	@Override
	public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain)
			throws IOException, ServletException {
		HttpServletRequest request = (HttpServletRequest) req;
		HttpServletResponse response = (HttpServletResponse) res;
		HttpSession session = request.getSession(true);
		User user = (User) session.getAttribute("123");
		String servletPath = request.getServletPath();
		if (!checkExRoute(servletPath) && user == null) {// session过期处理
			String userClient = request.getHeader("user-agent");
			_log.warn("用户未登录或会话已经过期，请重新登录！");
			_log.warn("客户端浏览器类型:" + userClient);
			String contextPath = request.getContextPath();
			response.sendRedirect(contextPath + "/page/login.jsp");
			return;
		}
		_log.info("............请求路径 ：" + servletPath + " 有效放行...........");
		// 登录有效放行
		chain.doFilter(request, response);
	}

	@SuppressWarnings("unchecked")
	@Override
	public void init(FilterConfig conf) throws ServletException {
		// 要排除的请求路径配置在web.xml的filter初始化参数的名称集合
		Enumeration<String> exNames;
		exNames = conf.getInitParameterNames();
		if (null != exNames) {
			// 要排除的请求路径在配置文件中的名称
			String exName;
			// 要排除的请求路径
			String exRoute;
			while (exNames.hasMoreElements()) {
				exName = (String) exNames.nextElement();
				exRoute = conf.getInitParameter(exName);
				exRoutes.add(exRoute);
			}
		}

	}
	
	/**
	 * 
	 * @Method: checkExRoute  
	 * @Description: 验证当前请求路径是否在要排除的范围内
	 * @param reqPath
	 * @return boolean  
	 * @author : peili 
	 * @CreateDate : 2016年8月12日 下午5:09:42
	 */
	private boolean checkExRoute(String reqPath) {
		boolean flag = false;
		for (String exPath : exRoutes) {
			if (reqPath.contains(exPath)) {
				flag = true;
				break;
			}
		}
		return flag;
	}

}
