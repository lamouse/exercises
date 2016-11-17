package com.wxc.manage.web.taglib;

import org.springframework.util.CollectionUtils;



public class Functions {

	public static boolean in(Iterable<?> iterable, Object element) {
		if (iterable == null) {
			return false;
		}
		return CollectionUtils.contains(iterable.iterator(), element);
	}

}
