package com.wxc.manage.ctrl.user;

import com.wxc.manage.model.User;
import com.wxc.manage.service.user.UserService;
import org.springframework.asm.commons.Method;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

/**
 * Created by sora on 16/11/16 -016.
 */
@Controller
public class UserAction {
    @Autowired
    private UserService userService;

    @RequestMapping(value = "getUsers", produces = "application/json;charset=UTF-8", method = {RequestMethod.POST, RequestMethod.GET})
    @ResponseBody
   public List<User> getUser(int page, int pageSize){
        return userService.getUserByPage(page, pageSize);
    }
}
