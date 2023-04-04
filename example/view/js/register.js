let actionBtn = document.querySelector(".action");
let backBtn = document.querySelector(".back");

let userId = document.querySelector(".userId");
let userPwd = document.querySelector(".userPwd");
let ackPwd = document.querySelector(".ackPwd");

// 判断账号密码的长度，是否符合6-16位，且两次输入密码是否相等
function valueLen() {
    if (
        (userId.value.length > 16 || userId.value.length < 6) || (userPwd.value.length > 16 || userPwd.value.length < 6) || (ackPwd.value.length > 16 || ackPwd.value.length < 6)
    ) {
        alert("请输入6-16位的账号或密码");
        return;
    } else if (userPwd.value != ackPwd.value) {
        alert("您两次输入的密码不一致，请仔细确认");
        return;
    }
}

// “注册” 按钮
function action() {
    valueLen();
    
}

// “返回” 按钮
function back() {

}

// “注册” 按钮
actionBtn.onclick = action;

// “返回” 按钮
backBtn.onclick = back;