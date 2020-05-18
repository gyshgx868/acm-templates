# ACM/ICPC Templates

该仓库存储了本人在本科期间参加ACM/ICPC所使用的一些常用算法模板。

目前该仓库中的大部分代码已经使用现代`C++11`进行重写，将大量的指针或者数组改写为了`std::vector`，并将一些函数封装为了模板类，因此在某些算法实现上可能会带来一些性能问题。

该模板库由LaTeX进行组织编写，但是大部分的算法仍然缺乏描述。若在使用过程中发现错误，或者有更好的代码以及教程性的描述文字，欢迎提交Pull Requests。

**注:** 部分描述文字或者源代码已经无法找到确切的出处，如有侵权行为请及时联系删除，谢谢。

## 编译PDF

首先，克隆该仓库：

```
git clone https://github.com/gyshgx868/acm-templates.git
```

然后，在命令行下执行（或者直接使用相关的TeX IDE进行编译）：

```
xelatex main.tex
```

**注:** 编译PDF需要安装相应的TeX环境，如：

 - [TeX Live](https://www.tug.org/texlive)
 - [MacTeX](https://tug.org/mactex)

更详细的环境配置请参考相关的教程。

## 致谢

本仓库中的模板大部分修改自：

 - [fz568573448](https://github.com/fz568573448/ACM-ICPC-Template)
 - [OI Wiki](https://oi-wiki.org/)
