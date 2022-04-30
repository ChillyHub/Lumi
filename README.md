# Lumi

*Lumi Engine : my first experimental engine.*



#### 已实现的功能

- 简易的日志系统
- 简易的事件系统
- 简易的实体组件系统
- 基础的2D, 3D渲染，与帧缓冲
- 批处理
- Gizmos
- 文件序列化



#### 外部库

- GLFW :  基于 OpenGL 的窗口库
- entt :  实体组件系统 (ECS) 库
- glad :  OpenGL API 接口
- glm :  数学库
- imgui :  即时 UI 库
- spdlog :  日志库
- stb :  文件加载库



#### 接下来的计划

- 实现异步文件 IO
- Mesh 组件实现
- 加入对 Vulkan 的支持
- 添加多种不同shader
- Light 组件实现，实现阴影
- 简单的刚体碰撞支持
- 之后此版代码将停止更新，另起项目进行重构，减少虚拟化，实现完善的反射机制，考虑使用线程池实现建议的多线程调度，并加入更多的高级渲染功能和后期处理，几何体处理功能，更丰富的物理系统



#### 平台与编译环境

- Windows10 及以上
- OpenGL 4.6
- Visual Studio 2022
- C++20



#### 构建

使用 premake 构建 VS 解决方案，建议使用 Visual Studio 2022

可以运行 `script/build.bat` 直接构建