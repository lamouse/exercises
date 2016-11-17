package com.wxc.manage.service.user;

import com.wxc.manage.model.User;

import java.util.List;

/**
 * Created by sora on 16/11/16 -016.
 */
public interface UserService {
    /**
     * @param page
     * @param pageSize
     * @return User
     */
    List<User> getUserByPage(int page, int pageSize);
}
