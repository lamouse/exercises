package com.wxc.manage.service.user.impl;

import com.github.pagehelper.PageHelper;
import com.wxc.manage.mapper.UserMapper;
import com.wxc.manage.model.User;
import com.wxc.manage.service.user.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * Created by sora on 16/11/16 -016.
 */
@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public List<User> getUserByPage(int page, int pageSize) {
        PageHelper.startPage(page, pageSize);
        List<User> users = userMapper.selectAll();
        return users;
    }
}
