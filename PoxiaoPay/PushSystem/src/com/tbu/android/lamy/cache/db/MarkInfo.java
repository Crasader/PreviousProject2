package com.tbu.android.lamy.cache.db;

/**
 * 缓存Push信息
 * @author molo
 *
 */
public class MarkInfo {

	private int id;
	/**
	 * 拼接好的上传服务端的POST字符串
	 */
	private String content;
	
	public MarkInfo(int id, String content) {
		super();
		this.id = id;
		this.content = content;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}
	
	@Override
	public String toString() {
		return "{id:" + getId() + ",content:"+getContent() + "}" ;
	}
}
