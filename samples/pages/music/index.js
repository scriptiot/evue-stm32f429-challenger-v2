router  = require("@system.router")

export default {
    data: {
        title: 'PingFanZhiLu'
    },
    onInit: function () {
        print("==========onInit progress==========")
    },

    onReady: function () {
        print("==========onReady progress==========")
    },

    onShow: function () {
        print("==========onShow progress==========")
    },

    onHide: function () {
        print("==========onHide progress==========")
    },
    
    onDestroy: function () {
        print("==========onDestroy progress==========")
    },

    onReturn: function() {
        router.push({ uri: "pages/dock/index" })
    }
}
