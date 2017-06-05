package com.t.h.domain.payswtich.test;

import com.t.h.domain.payswtich.PSwitchManage;

public class PSwitchTest {
	public static void main(String[] args) {
		String list = "{ {\"b\" : \"20\"}, {\"tat\" : \"12\"} }";
		PSwitchManage.getPSwtich("999999","100,200,300",list);
	}
}
