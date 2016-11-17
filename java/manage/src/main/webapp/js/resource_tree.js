/**
 * 设置zTree树
 */
var setting = {
	async: {
		enable: true,
		url: getUrlByNodeId
	},
	check: {
		enable: false
	},
	data: {
		simpleData: {
			enable: true
		}
	},
	view: {
		expandSpeed: ""
	},
	callback: {
		beforeExpand: beforeExpand,
		onAsyncSuccess: onAsyncSuccess,
		onAsyncError: onAsyncError,
		onClick: zTreeOnClick
	}
};

/**
 * 功能：通过NodeId获得节点的孩子节点
 * 调用：当父节点展开时，调用，返回该父节点的子节点
 * 后台数据格式：JSON
 * @param treeId 树控件的Id
 * @param treeNode 树节点对象：包含Id等信息
 * @return
 */
function getUrlByNodeId(treeId, treeNode) {
	return rootPath + 'resource/getResourceByNode.do?parentId=' + treeNode.id;
}
/**
 * 展开之前执行的函数
 * @param treeId
 * @param treeNode
 * @return
 */
function beforeExpand(treeId, treeNode) {
	if (!treeNode.isAjaxing) {
		ajaxGetNodes(treeNode, "refresh");
		return true;
	} else {
		alert("Loading...");
		return false;
	}
}
/**
 * 加载成功后执行的函数
 * @param event 封装了js的事件
 * @param treeId 树控件的Id
 * @param treeNode 树节点对象
 * @param msg 返回的JSON格式的消息
 * @return
 */
function onAsyncSuccess(event, treeId, treeNode, msg) {
	if (!msg || msg.length == 0) {
		return;
	}
	var zTree = $.fn.zTree.getZTreeObj("resourceTree");
	treeNode.icon = "";
	zTree.updateNode(treeNode);//更新树结构
	zTree.selectNode(treeNode.children[0]);//设置为第一个子节点为选中状态
}
function onAsyncError(event, treeId, treeNode, XMLHttpRequest, textStatus, errorThrown) {
	var zTree = $.fn.zTree.getZTreeObj("resourceTree");
	alert("Error ! 异步获取数据异常");
	treeNode.icon = "";
	zTree.updateNode(treeNode);
}
function ajaxGetNodes(treeNode, reloadType) {
	var zTree = $.fn.zTree.getZTreeObj("resourceTree");
	if (reloadType == "refresh") {
		treeNode.icon = rootPath + "css/zTreeStyle/img/loading.gif";
		zTree.updateNode(treeNode);
	}
	zTree.reAsyncChildNodes(treeNode, reloadType, true);
}
function setCenterUrl(url){
	var p = $('#bodyDiv').layout('panel','center'); 
	p.panel('refresh',rootPath + url);
}
/**
 * 功能：当点击树节点时，调用该函数
 * @param event
 * @param treeId
 * @param treeNode
 * @return
 */
function zTreeOnClick(event, treeId, treeNode) {
	$('#resource_dg').datagrid({url:rootPath + 'resource/allResourceByNodeId.do',
		queryParams:{parentId: treeNode.id
			,isParent: treeNode.isParent}});
}
var zNodes = new Array();
$(document).ready(function(){
	$.ajax({  
	    type: 'POST',
	    dataType: "json",
	    url:rootPath+'resource/getResourceByNode.do?parentId=0',
	    success: function(data){
	    	 $.each(data,function(i,n){
	             zNodes[i] = {"id": n.id, "name": n.name, "isParent": n.isParent, "iconOpen": n.iconOpen, "iconClose": n.iconClose};
	            });
	    	 $.fn.zTree.init($("#resourceTree"), setting, zNodes);
	    }
	}); 
});


