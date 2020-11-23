router = require("@system.router")

export default {
    data: {
        title: 'Keyboard'
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

    onReturn: function () {
        router.push({ uri: "pages/call/index" })
    },

    onCall: function () {
        router.push({ uri: "pages/calling/index" })
    }
}