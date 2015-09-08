## Spine Runtimes

对spine runtime进行修改，新增BatchSkeletonAnimation类（继承自SkeletonAnimation），使用QuadCommand代替spine原有的CustomCommand,使spine的渲染过程能够利用Cocos2d-x的 Auto-Batch机制，降低Gl-call次数。
##效果比对
SkeletonAnimation：Draw Call 28次
![](https://raw.githubusercontent.com/dzfish/spine-runtimes/master/spine-cocos2dx/3/example/skeleton.jpg)  

BatchSkeletonAnimation：Draw Call 1次
![](https://raw.githubusercontent.com/dzfish/spine-runtimes/master/spine-cocos2dx/3/example/batchskeleton.jpg)  

## Versioning

支持cocos2dx-3.3及以上
