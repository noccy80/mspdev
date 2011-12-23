



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 (function(){function a(e){this.t={};this.tick=function(f,c,d){c=d!=undefined?d:(new Date).getTime();this.t[f]=c};this.tick("start",null,e)}var b=new a;window.jstiming={Timer:a,load:b};try{var g=null;if(window.chrome&&window.chrome.csi)g=Math.floor(window.chrome.csi().pageT);if(g==null)if(window.gtbExternal)g=window.gtbExternal.pageT();if(g==null)if(window.external)g=window.external.pageT;if(g)window.jstiming.pt=g}catch(h){};})();

 
 
 
 var codesite_token = "c6974bcd72eb95455827185f7306e1fa";
 
 
 var logged_in_user_email = "Dung.Dang@gmail.com";
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>PMatrix2D.java - 
 processing -
 
 Project Hosting on Google Code</title>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/10276742928614796628/css/ph_core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/10276742928614796628/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/10276742928614796628/css/d_sb_20080522.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/10276742928614796628/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 margin-bottom:0;
}

 </style>
</head>
<body class="t4">
 <script type="text/javascript">
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 </script>
<div class="headbg">
 <div id="gaia">
 
 <span>
 
 
 <b>Dung.Dang@gmail.com</b>
 
 
 | <a href="/u/@VhVRRVJYBRNNWwl6/" id="projects-dropdown" onclick="return false;"
 ><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="/u/@VhVRRVJYBRNNWwl6/" onclick="_CS_click('/gb/ph/profile');" 
 title="Profile, Updates, and Settings"
 ><u>Profile</u></a>
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fprocessing%2Fsource%2Fbrowse%2Ftrunk%2Fprocessing%2Fcore%2Fsrc%2Fprocessing%2Fcore%2FPMatrix2D.java" 
 onclick="_CS_click('/gb/ph/signout');"
 ><u>Sign out</u></a>
 
 </span>

 </div>
 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->




 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0">
 <tr style="height: 58px;">
 
 <td id="plogo">
 <a href="/p/processing/">
 
 <img src="http://www.gstatic.com/codesite/ph/images/defaultlogo.png" alt="Logo">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/processing/">processing</a>
 </div>
 <div id="psum">
 <a id="project_summary_link" href="/p/processing/" >An open source programming language and environment for images, animation, and interactions.</a>
 
 </div>
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/processing/" class="tab ">Project&nbsp;Home</a> 
 
 
 
 
 <a href="/p/processing/downloads/list" class="tab ">Downloads</a>
 
 
 
 
 
 <a href="/p/processing/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/processing/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/processing/source/checkout"
 class="tab active">Source</a>
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 
 
 <span class="inst1"><a href="/p/processing/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/processing/source/browse/trunk/processing">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/processing/source/list">Changes</a></span> &nbsp;
 
 <form action="http://www.google.com/codesearch" method="get" style="display:inline"
 onsubmit="document.getElementById('codesearchq').value = document.getElementById('origq').value + ' package:http://processing\\.googlecode\\.com'">
 <input type="hidden" name="q" id="codesearchq" value="">
 <input type="text" maxlength="2048" size="38" id="origq" name="origq" value="" title="Google Code Search" style="font-size:92%">&nbsp;<input type="submit" value="Search Trunk" name="btnG" style="font-size:92%">
 
 
 
 </form>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>
<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>


<div id="maincol"
 
>

 
<!-- IE -->




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/processing/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/processing/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/">core</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/">src</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/">core</a><span class="sp">/&nbsp;</span>PMatrix2D.java</span>
 
 

 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix2D.java?edit=1"
 ><img src="http://www.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix2D.java?r=6524" title="Previous">&lsaquo;r6524</a></li>
 
 </ul>
 </td>
 
 <td class="flipper"><b>r7768</b></td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(http://www.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn7768_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn7768_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn7768_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn7768_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn7768_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn7768_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn7768_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn7768_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn7768_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn7768_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn7768_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn7768_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn7768_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn7768_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn7768_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn7768_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn7768_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn7768_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn7768_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn7768_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn7768_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn7768_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn7768_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn7768_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn7768_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn7768_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn7768_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn7768_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn7768_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn7768_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn7768_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn7768_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn7768_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn7768_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn7768_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn7768_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn7768_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn7768_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn7768_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn7768_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn7768_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn7768_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn7768_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn7768_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn7768_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn7768_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn7768_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn7768_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn7768_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn7768_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn7768_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn7768_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn7768_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn7768_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn7768_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn7768_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn7768_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn7768_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn7768_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn7768_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn7768_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn7768_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn7768_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn7768_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn7768_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn7768_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn7768_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn7768_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn7768_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn7768_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn7768_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn7768_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn7768_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn7768_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn7768_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn7768_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn7768_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn7768_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn7768_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn7768_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn7768_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn7768_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn7768_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn7768_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn7768_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn7768_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn7768_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn7768_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn7768_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn7768_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn7768_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn7768_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn7768_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn7768_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn7768_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn7768_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn7768_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn7768_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn7768_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn7768_100"

><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn7768_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn7768_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn7768_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn7768_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn7768_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn7768_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn7768_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn7768_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn7768_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn7768_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn7768_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn7768_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn7768_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn7768_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn7768_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn7768_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn7768_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn7768_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn7768_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn7768_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn7768_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn7768_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn7768_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn7768_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn7768_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn7768_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn7768_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn7768_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn7768_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn7768_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn7768_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn7768_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn7768_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn7768_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn7768_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn7768_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn7768_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn7768_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn7768_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn7768_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn7768_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn7768_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn7768_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn7768_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn7768_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn7768_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn7768_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn7768_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn7768_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn7768_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn7768_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn7768_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn7768_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn7768_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn7768_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn7768_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn7768_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn7768_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn7768_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn7768_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn7768_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn7768_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn7768_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn7768_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn7768_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn7768_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn7768_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn7768_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn7768_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn7768_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn7768_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn7768_172"

><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn7768_173"

><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn7768_174"

><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn7768_175"

><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn7768_176"

><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn7768_177"

><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn7768_178"

><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn7768_179"

><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn7768_180"

><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn7768_181"

><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn7768_182"

><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn7768_183"

><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn7768_184"

><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn7768_185"

><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn7768_186"

><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn7768_187"

><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn7768_188"

><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn7768_189"

><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn7768_190"

><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn7768_191"

><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn7768_192"

><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn7768_193"

><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn7768_194"

><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn7768_195"

><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn7768_196"

><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn7768_197"

><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn7768_198"

><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn7768_199"

><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn7768_200"

><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn7768_201"

><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn7768_202"

><td id="202"><a href="#202">202</a></td></tr
><tr id="gr_svn7768_203"

><td id="203"><a href="#203">203</a></td></tr
><tr id="gr_svn7768_204"

><td id="204"><a href="#204">204</a></td></tr
><tr id="gr_svn7768_205"

><td id="205"><a href="#205">205</a></td></tr
><tr id="gr_svn7768_206"

><td id="206"><a href="#206">206</a></td></tr
><tr id="gr_svn7768_207"

><td id="207"><a href="#207">207</a></td></tr
><tr id="gr_svn7768_208"

><td id="208"><a href="#208">208</a></td></tr
><tr id="gr_svn7768_209"

><td id="209"><a href="#209">209</a></td></tr
><tr id="gr_svn7768_210"

><td id="210"><a href="#210">210</a></td></tr
><tr id="gr_svn7768_211"

><td id="211"><a href="#211">211</a></td></tr
><tr id="gr_svn7768_212"

><td id="212"><a href="#212">212</a></td></tr
><tr id="gr_svn7768_213"

><td id="213"><a href="#213">213</a></td></tr
><tr id="gr_svn7768_214"

><td id="214"><a href="#214">214</a></td></tr
><tr id="gr_svn7768_215"

><td id="215"><a href="#215">215</a></td></tr
><tr id="gr_svn7768_216"

><td id="216"><a href="#216">216</a></td></tr
><tr id="gr_svn7768_217"

><td id="217"><a href="#217">217</a></td></tr
><tr id="gr_svn7768_218"

><td id="218"><a href="#218">218</a></td></tr
><tr id="gr_svn7768_219"

><td id="219"><a href="#219">219</a></td></tr
><tr id="gr_svn7768_220"

><td id="220"><a href="#220">220</a></td></tr
><tr id="gr_svn7768_221"

><td id="221"><a href="#221">221</a></td></tr
><tr id="gr_svn7768_222"

><td id="222"><a href="#222">222</a></td></tr
><tr id="gr_svn7768_223"

><td id="223"><a href="#223">223</a></td></tr
><tr id="gr_svn7768_224"

><td id="224"><a href="#224">224</a></td></tr
><tr id="gr_svn7768_225"

><td id="225"><a href="#225">225</a></td></tr
><tr id="gr_svn7768_226"

><td id="226"><a href="#226">226</a></td></tr
><tr id="gr_svn7768_227"

><td id="227"><a href="#227">227</a></td></tr
><tr id="gr_svn7768_228"

><td id="228"><a href="#228">228</a></td></tr
><tr id="gr_svn7768_229"

><td id="229"><a href="#229">229</a></td></tr
><tr id="gr_svn7768_230"

><td id="230"><a href="#230">230</a></td></tr
><tr id="gr_svn7768_231"

><td id="231"><a href="#231">231</a></td></tr
><tr id="gr_svn7768_232"

><td id="232"><a href="#232">232</a></td></tr
><tr id="gr_svn7768_233"

><td id="233"><a href="#233">233</a></td></tr
><tr id="gr_svn7768_234"

><td id="234"><a href="#234">234</a></td></tr
><tr id="gr_svn7768_235"

><td id="235"><a href="#235">235</a></td></tr
><tr id="gr_svn7768_236"

><td id="236"><a href="#236">236</a></td></tr
><tr id="gr_svn7768_237"

><td id="237"><a href="#237">237</a></td></tr
><tr id="gr_svn7768_238"

><td id="238"><a href="#238">238</a></td></tr
><tr id="gr_svn7768_239"

><td id="239"><a href="#239">239</a></td></tr
><tr id="gr_svn7768_240"

><td id="240"><a href="#240">240</a></td></tr
><tr id="gr_svn7768_241"

><td id="241"><a href="#241">241</a></td></tr
><tr id="gr_svn7768_242"

><td id="242"><a href="#242">242</a></td></tr
><tr id="gr_svn7768_243"

><td id="243"><a href="#243">243</a></td></tr
><tr id="gr_svn7768_244"

><td id="244"><a href="#244">244</a></td></tr
><tr id="gr_svn7768_245"

><td id="245"><a href="#245">245</a></td></tr
><tr id="gr_svn7768_246"

><td id="246"><a href="#246">246</a></td></tr
><tr id="gr_svn7768_247"

><td id="247"><a href="#247">247</a></td></tr
><tr id="gr_svn7768_248"

><td id="248"><a href="#248">248</a></td></tr
><tr id="gr_svn7768_249"

><td id="249"><a href="#249">249</a></td></tr
><tr id="gr_svn7768_250"

><td id="250"><a href="#250">250</a></td></tr
><tr id="gr_svn7768_251"

><td id="251"><a href="#251">251</a></td></tr
><tr id="gr_svn7768_252"

><td id="252"><a href="#252">252</a></td></tr
><tr id="gr_svn7768_253"

><td id="253"><a href="#253">253</a></td></tr
><tr id="gr_svn7768_254"

><td id="254"><a href="#254">254</a></td></tr
><tr id="gr_svn7768_255"

><td id="255"><a href="#255">255</a></td></tr
><tr id="gr_svn7768_256"

><td id="256"><a href="#256">256</a></td></tr
><tr id="gr_svn7768_257"

><td id="257"><a href="#257">257</a></td></tr
><tr id="gr_svn7768_258"

><td id="258"><a href="#258">258</a></td></tr
><tr id="gr_svn7768_259"

><td id="259"><a href="#259">259</a></td></tr
><tr id="gr_svn7768_260"

><td id="260"><a href="#260">260</a></td></tr
><tr id="gr_svn7768_261"

><td id="261"><a href="#261">261</a></td></tr
><tr id="gr_svn7768_262"

><td id="262"><a href="#262">262</a></td></tr
><tr id="gr_svn7768_263"

><td id="263"><a href="#263">263</a></td></tr
><tr id="gr_svn7768_264"

><td id="264"><a href="#264">264</a></td></tr
><tr id="gr_svn7768_265"

><td id="265"><a href="#265">265</a></td></tr
><tr id="gr_svn7768_266"

><td id="266"><a href="#266">266</a></td></tr
><tr id="gr_svn7768_267"

><td id="267"><a href="#267">267</a></td></tr
><tr id="gr_svn7768_268"

><td id="268"><a href="#268">268</a></td></tr
><tr id="gr_svn7768_269"

><td id="269"><a href="#269">269</a></td></tr
><tr id="gr_svn7768_270"

><td id="270"><a href="#270">270</a></td></tr
><tr id="gr_svn7768_271"

><td id="271"><a href="#271">271</a></td></tr
><tr id="gr_svn7768_272"

><td id="272"><a href="#272">272</a></td></tr
><tr id="gr_svn7768_273"

><td id="273"><a href="#273">273</a></td></tr
><tr id="gr_svn7768_274"

><td id="274"><a href="#274">274</a></td></tr
><tr id="gr_svn7768_275"

><td id="275"><a href="#275">275</a></td></tr
><tr id="gr_svn7768_276"

><td id="276"><a href="#276">276</a></td></tr
><tr id="gr_svn7768_277"

><td id="277"><a href="#277">277</a></td></tr
><tr id="gr_svn7768_278"

><td id="278"><a href="#278">278</a></td></tr
><tr id="gr_svn7768_279"

><td id="279"><a href="#279">279</a></td></tr
><tr id="gr_svn7768_280"

><td id="280"><a href="#280">280</a></td></tr
><tr id="gr_svn7768_281"

><td id="281"><a href="#281">281</a></td></tr
><tr id="gr_svn7768_282"

><td id="282"><a href="#282">282</a></td></tr
><tr id="gr_svn7768_283"

><td id="283"><a href="#283">283</a></td></tr
><tr id="gr_svn7768_284"

><td id="284"><a href="#284">284</a></td></tr
><tr id="gr_svn7768_285"

><td id="285"><a href="#285">285</a></td></tr
><tr id="gr_svn7768_286"

><td id="286"><a href="#286">286</a></td></tr
><tr id="gr_svn7768_287"

><td id="287"><a href="#287">287</a></td></tr
><tr id="gr_svn7768_288"

><td id="288"><a href="#288">288</a></td></tr
><tr id="gr_svn7768_289"

><td id="289"><a href="#289">289</a></td></tr
><tr id="gr_svn7768_290"

><td id="290"><a href="#290">290</a></td></tr
><tr id="gr_svn7768_291"

><td id="291"><a href="#291">291</a></td></tr
><tr id="gr_svn7768_292"

><td id="292"><a href="#292">292</a></td></tr
><tr id="gr_svn7768_293"

><td id="293"><a href="#293">293</a></td></tr
><tr id="gr_svn7768_294"

><td id="294"><a href="#294">294</a></td></tr
><tr id="gr_svn7768_295"

><td id="295"><a href="#295">295</a></td></tr
><tr id="gr_svn7768_296"

><td id="296"><a href="#296">296</a></td></tr
><tr id="gr_svn7768_297"

><td id="297"><a href="#297">297</a></td></tr
><tr id="gr_svn7768_298"

><td id="298"><a href="#298">298</a></td></tr
><tr id="gr_svn7768_299"

><td id="299"><a href="#299">299</a></td></tr
><tr id="gr_svn7768_300"

><td id="300"><a href="#300">300</a></td></tr
><tr id="gr_svn7768_301"

><td id="301"><a href="#301">301</a></td></tr
><tr id="gr_svn7768_302"

><td id="302"><a href="#302">302</a></td></tr
><tr id="gr_svn7768_303"

><td id="303"><a href="#303">303</a></td></tr
><tr id="gr_svn7768_304"

><td id="304"><a href="#304">304</a></td></tr
><tr id="gr_svn7768_305"

><td id="305"><a href="#305">305</a></td></tr
><tr id="gr_svn7768_306"

><td id="306"><a href="#306">306</a></td></tr
><tr id="gr_svn7768_307"

><td id="307"><a href="#307">307</a></td></tr
><tr id="gr_svn7768_308"

><td id="308"><a href="#308">308</a></td></tr
><tr id="gr_svn7768_309"

><td id="309"><a href="#309">309</a></td></tr
><tr id="gr_svn7768_310"

><td id="310"><a href="#310">310</a></td></tr
><tr id="gr_svn7768_311"

><td id="311"><a href="#311">311</a></td></tr
><tr id="gr_svn7768_312"

><td id="312"><a href="#312">312</a></td></tr
><tr id="gr_svn7768_313"

><td id="313"><a href="#313">313</a></td></tr
><tr id="gr_svn7768_314"

><td id="314"><a href="#314">314</a></td></tr
><tr id="gr_svn7768_315"

><td id="315"><a href="#315">315</a></td></tr
><tr id="gr_svn7768_316"

><td id="316"><a href="#316">316</a></td></tr
><tr id="gr_svn7768_317"

><td id="317"><a href="#317">317</a></td></tr
><tr id="gr_svn7768_318"

><td id="318"><a href="#318">318</a></td></tr
><tr id="gr_svn7768_319"

><td id="319"><a href="#319">319</a></td></tr
><tr id="gr_svn7768_320"

><td id="320"><a href="#320">320</a></td></tr
><tr id="gr_svn7768_321"

><td id="321"><a href="#321">321</a></td></tr
><tr id="gr_svn7768_322"

><td id="322"><a href="#322">322</a></td></tr
><tr id="gr_svn7768_323"

><td id="323"><a href="#323">323</a></td></tr
><tr id="gr_svn7768_324"

><td id="324"><a href="#324">324</a></td></tr
><tr id="gr_svn7768_325"

><td id="325"><a href="#325">325</a></td></tr
><tr id="gr_svn7768_326"

><td id="326"><a href="#326">326</a></td></tr
><tr id="gr_svn7768_327"

><td id="327"><a href="#327">327</a></td></tr
><tr id="gr_svn7768_328"

><td id="328"><a href="#328">328</a></td></tr
><tr id="gr_svn7768_329"

><td id="329"><a href="#329">329</a></td></tr
><tr id="gr_svn7768_330"

><td id="330"><a href="#330">330</a></td></tr
><tr id="gr_svn7768_331"

><td id="331"><a href="#331">331</a></td></tr
><tr id="gr_svn7768_332"

><td id="332"><a href="#332">332</a></td></tr
><tr id="gr_svn7768_333"

><td id="333"><a href="#333">333</a></td></tr
><tr id="gr_svn7768_334"

><td id="334"><a href="#334">334</a></td></tr
><tr id="gr_svn7768_335"

><td id="335"><a href="#335">335</a></td></tr
><tr id="gr_svn7768_336"

><td id="336"><a href="#336">336</a></td></tr
><tr id="gr_svn7768_337"

><td id="337"><a href="#337">337</a></td></tr
><tr id="gr_svn7768_338"

><td id="338"><a href="#338">338</a></td></tr
><tr id="gr_svn7768_339"

><td id="339"><a href="#339">339</a></td></tr
><tr id="gr_svn7768_340"

><td id="340"><a href="#340">340</a></td></tr
><tr id="gr_svn7768_341"

><td id="341"><a href="#341">341</a></td></tr
><tr id="gr_svn7768_342"

><td id="342"><a href="#342">342</a></td></tr
><tr id="gr_svn7768_343"

><td id="343"><a href="#343">343</a></td></tr
><tr id="gr_svn7768_344"

><td id="344"><a href="#344">344</a></td></tr
><tr id="gr_svn7768_345"

><td id="345"><a href="#345">345</a></td></tr
><tr id="gr_svn7768_346"

><td id="346"><a href="#346">346</a></td></tr
><tr id="gr_svn7768_347"

><td id="347"><a href="#347">347</a></td></tr
><tr id="gr_svn7768_348"

><td id="348"><a href="#348">348</a></td></tr
><tr id="gr_svn7768_349"

><td id="349"><a href="#349">349</a></td></tr
><tr id="gr_svn7768_350"

><td id="350"><a href="#350">350</a></td></tr
><tr id="gr_svn7768_351"

><td id="351"><a href="#351">351</a></td></tr
><tr id="gr_svn7768_352"

><td id="352"><a href="#352">352</a></td></tr
><tr id="gr_svn7768_353"

><td id="353"><a href="#353">353</a></td></tr
><tr id="gr_svn7768_354"

><td id="354"><a href="#354">354</a></td></tr
><tr id="gr_svn7768_355"

><td id="355"><a href="#355">355</a></td></tr
><tr id="gr_svn7768_356"

><td id="356"><a href="#356">356</a></td></tr
><tr id="gr_svn7768_357"

><td id="357"><a href="#357">357</a></td></tr
><tr id="gr_svn7768_358"

><td id="358"><a href="#358">358</a></td></tr
><tr id="gr_svn7768_359"

><td id="359"><a href="#359">359</a></td></tr
><tr id="gr_svn7768_360"

><td id="360"><a href="#360">360</a></td></tr
><tr id="gr_svn7768_361"

><td id="361"><a href="#361">361</a></td></tr
><tr id="gr_svn7768_362"

><td id="362"><a href="#362">362</a></td></tr
><tr id="gr_svn7768_363"

><td id="363"><a href="#363">363</a></td></tr
><tr id="gr_svn7768_364"

><td id="364"><a href="#364">364</a></td></tr
><tr id="gr_svn7768_365"

><td id="365"><a href="#365">365</a></td></tr
><tr id="gr_svn7768_366"

><td id="366"><a href="#366">366</a></td></tr
><tr id="gr_svn7768_367"

><td id="367"><a href="#367">367</a></td></tr
><tr id="gr_svn7768_368"

><td id="368"><a href="#368">368</a></td></tr
><tr id="gr_svn7768_369"

><td id="369"><a href="#369">369</a></td></tr
><tr id="gr_svn7768_370"

><td id="370"><a href="#370">370</a></td></tr
><tr id="gr_svn7768_371"

><td id="371"><a href="#371">371</a></td></tr
><tr id="gr_svn7768_372"

><td id="372"><a href="#372">372</a></td></tr
><tr id="gr_svn7768_373"

><td id="373"><a href="#373">373</a></td></tr
><tr id="gr_svn7768_374"

><td id="374"><a href="#374">374</a></td></tr
><tr id="gr_svn7768_375"

><td id="375"><a href="#375">375</a></td></tr
><tr id="gr_svn7768_376"

><td id="376"><a href="#376">376</a></td></tr
><tr id="gr_svn7768_377"

><td id="377"><a href="#377">377</a></td></tr
><tr id="gr_svn7768_378"

><td id="378"><a href="#378">378</a></td></tr
><tr id="gr_svn7768_379"

><td id="379"><a href="#379">379</a></td></tr
><tr id="gr_svn7768_380"

><td id="380"><a href="#380">380</a></td></tr
><tr id="gr_svn7768_381"

><td id="381"><a href="#381">381</a></td></tr
><tr id="gr_svn7768_382"

><td id="382"><a href="#382">382</a></td></tr
><tr id="gr_svn7768_383"

><td id="383"><a href="#383">383</a></td></tr
><tr id="gr_svn7768_384"

><td id="384"><a href="#384">384</a></td></tr
><tr id="gr_svn7768_385"

><td id="385"><a href="#385">385</a></td></tr
><tr id="gr_svn7768_386"

><td id="386"><a href="#386">386</a></td></tr
><tr id="gr_svn7768_387"

><td id="387"><a href="#387">387</a></td></tr
><tr id="gr_svn7768_388"

><td id="388"><a href="#388">388</a></td></tr
><tr id="gr_svn7768_389"

><td id="389"><a href="#389">389</a></td></tr
><tr id="gr_svn7768_390"

><td id="390"><a href="#390">390</a></td></tr
><tr id="gr_svn7768_391"

><td id="391"><a href="#391">391</a></td></tr
><tr id="gr_svn7768_392"

><td id="392"><a href="#392">392</a></td></tr
><tr id="gr_svn7768_393"

><td id="393"><a href="#393">393</a></td></tr
><tr id="gr_svn7768_394"

><td id="394"><a href="#394">394</a></td></tr
><tr id="gr_svn7768_395"

><td id="395"><a href="#395">395</a></td></tr
><tr id="gr_svn7768_396"

><td id="396"><a href="#396">396</a></td></tr
><tr id="gr_svn7768_397"

><td id="397"><a href="#397">397</a></td></tr
><tr id="gr_svn7768_398"

><td id="398"><a href="#398">398</a></td></tr
><tr id="gr_svn7768_399"

><td id="399"><a href="#399">399</a></td></tr
><tr id="gr_svn7768_400"

><td id="400"><a href="#400">400</a></td></tr
><tr id="gr_svn7768_401"

><td id="401"><a href="#401">401</a></td></tr
><tr id="gr_svn7768_402"

><td id="402"><a href="#402">402</a></td></tr
><tr id="gr_svn7768_403"

><td id="403"><a href="#403">403</a></td></tr
><tr id="gr_svn7768_404"

><td id="404"><a href="#404">404</a></td></tr
><tr id="gr_svn7768_405"

><td id="405"><a href="#405">405</a></td></tr
><tr id="gr_svn7768_406"

><td id="406"><a href="#406">406</a></td></tr
><tr id="gr_svn7768_407"

><td id="407"><a href="#407">407</a></td></tr
><tr id="gr_svn7768_408"

><td id="408"><a href="#408">408</a></td></tr
><tr id="gr_svn7768_409"

><td id="409"><a href="#409">409</a></td></tr
><tr id="gr_svn7768_410"

><td id="410"><a href="#410">410</a></td></tr
><tr id="gr_svn7768_411"

><td id="411"><a href="#411">411</a></td></tr
><tr id="gr_svn7768_412"

><td id="412"><a href="#412">412</a></td></tr
><tr id="gr_svn7768_413"

><td id="413"><a href="#413">413</a></td></tr
><tr id="gr_svn7768_414"

><td id="414"><a href="#414">414</a></td></tr
><tr id="gr_svn7768_415"

><td id="415"><a href="#415">415</a></td></tr
><tr id="gr_svn7768_416"

><td id="416"><a href="#416">416</a></td></tr
><tr id="gr_svn7768_417"

><td id="417"><a href="#417">417</a></td></tr
><tr id="gr_svn7768_418"

><td id="418"><a href="#418">418</a></td></tr
><tr id="gr_svn7768_419"

><td id="419"><a href="#419">419</a></td></tr
><tr id="gr_svn7768_420"

><td id="420"><a href="#420">420</a></td></tr
><tr id="gr_svn7768_421"

><td id="421"><a href="#421">421</a></td></tr
><tr id="gr_svn7768_422"

><td id="422"><a href="#422">422</a></td></tr
><tr id="gr_svn7768_423"

><td id="423"><a href="#423">423</a></td></tr
><tr id="gr_svn7768_424"

><td id="424"><a href="#424">424</a></td></tr
><tr id="gr_svn7768_425"

><td id="425"><a href="#425">425</a></td></tr
><tr id="gr_svn7768_426"

><td id="426"><a href="#426">426</a></td></tr
><tr id="gr_svn7768_427"

><td id="427"><a href="#427">427</a></td></tr
><tr id="gr_svn7768_428"

><td id="428"><a href="#428">428</a></td></tr
><tr id="gr_svn7768_429"

><td id="429"><a href="#429">429</a></td></tr
><tr id="gr_svn7768_430"

><td id="430"><a href="#430">430</a></td></tr
><tr id="gr_svn7768_431"

><td id="431"><a href="#431">431</a></td></tr
><tr id="gr_svn7768_432"

><td id="432"><a href="#432">432</a></td></tr
><tr id="gr_svn7768_433"

><td id="433"><a href="#433">433</a></td></tr
><tr id="gr_svn7768_434"

><td id="434"><a href="#434">434</a></td></tr
><tr id="gr_svn7768_435"

><td id="435"><a href="#435">435</a></td></tr
><tr id="gr_svn7768_436"

><td id="436"><a href="#436">436</a></td></tr
><tr id="gr_svn7768_437"

><td id="437"><a href="#437">437</a></td></tr
><tr id="gr_svn7768_438"

><td id="438"><a href="#438">438</a></td></tr
><tr id="gr_svn7768_439"

><td id="439"><a href="#439">439</a></td></tr
><tr id="gr_svn7768_440"

><td id="440"><a href="#440">440</a></td></tr
><tr id="gr_svn7768_441"

><td id="441"><a href="#441">441</a></td></tr
><tr id="gr_svn7768_442"

><td id="442"><a href="#442">442</a></td></tr
><tr id="gr_svn7768_443"

><td id="443"><a href="#443">443</a></td></tr
><tr id="gr_svn7768_444"

><td id="444"><a href="#444">444</a></td></tr
><tr id="gr_svn7768_445"

><td id="445"><a href="#445">445</a></td></tr
><tr id="gr_svn7768_446"

><td id="446"><a href="#446">446</a></td></tr
><tr id="gr_svn7768_447"

><td id="447"><a href="#447">447</a></td></tr
><tr id="gr_svn7768_448"

><td id="448"><a href="#448">448</a></td></tr
><tr id="gr_svn7768_449"

><td id="449"><a href="#449">449</a></td></tr
><tr id="gr_svn7768_450"

><td id="450"><a href="#450">450</a></td></tr
><tr id="gr_svn7768_451"

><td id="451"><a href="#451">451</a></td></tr
><tr id="gr_svn7768_452"

><td id="452"><a href="#452">452</a></td></tr
><tr id="gr_svn7768_453"

><td id="453"><a href="#453">453</a></td></tr
><tr id="gr_svn7768_454"

><td id="454"><a href="#454">454</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint lang-java"><table id="src_table_0"><tr
id=sl_svn7768_1

><td class="source">/* -*- mode: java; c-basic-offset: 2; indent-tabs-mode: nil -*- */<br></td></tr
><tr
id=sl_svn7768_2

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3

><td class="source">/*<br></td></tr
><tr
id=sl_svn7768_4

><td class="source">  Part of the Processing project - http://processing.org<br></td></tr
><tr
id=sl_svn7768_5

><td class="source"><br></td></tr
><tr
id=sl_svn7768_6

><td class="source">  Copyright (c) 2005-08 Ben Fry and Casey Reas<br></td></tr
><tr
id=sl_svn7768_7

><td class="source"><br></td></tr
><tr
id=sl_svn7768_8

><td class="source">  This library is free software; you can redistribute it and/or<br></td></tr
><tr
id=sl_svn7768_9

><td class="source">  modify it under the terms of the GNU Lesser General Public<br></td></tr
><tr
id=sl_svn7768_10

><td class="source">  License as published by the Free Software Foundation; either<br></td></tr
><tr
id=sl_svn7768_11

><td class="source">  version 2.1 of the License, or (at your option) any later version.<br></td></tr
><tr
id=sl_svn7768_12

><td class="source"><br></td></tr
><tr
id=sl_svn7768_13

><td class="source">  This library is distributed in the hope that it will be useful,<br></td></tr
><tr
id=sl_svn7768_14

><td class="source">  but WITHOUT ANY WARRANTY; without even the implied warranty of<br></td></tr
><tr
id=sl_svn7768_15

><td class="source">  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU<br></td></tr
><tr
id=sl_svn7768_16

><td class="source">  Lesser General Public License for more details.<br></td></tr
><tr
id=sl_svn7768_17

><td class="source"><br></td></tr
><tr
id=sl_svn7768_18

><td class="source">  You should have received a copy of the GNU Lesser General<br></td></tr
><tr
id=sl_svn7768_19

><td class="source">  Public License along with this library; if not, write to the<br></td></tr
><tr
id=sl_svn7768_20

><td class="source">  Free Software Foundation, Inc., 59 Temple Place, Suite 330,<br></td></tr
><tr
id=sl_svn7768_21

><td class="source">  Boston, MA  02111-1307  USA<br></td></tr
><tr
id=sl_svn7768_22

><td class="source">*/<br></td></tr
><tr
id=sl_svn7768_23

><td class="source"><br></td></tr
><tr
id=sl_svn7768_24

><td class="source">package processing.core;<br></td></tr
><tr
id=sl_svn7768_25

><td class="source"><br></td></tr
><tr
id=sl_svn7768_26

><td class="source"><br></td></tr
><tr
id=sl_svn7768_27

><td class="source">/**<br></td></tr
><tr
id=sl_svn7768_28

><td class="source"> * 3x2 affine matrix implementation.<br></td></tr
><tr
id=sl_svn7768_29

><td class="source"> */<br></td></tr
><tr
id=sl_svn7768_30

><td class="source">public class PMatrix2D implements PMatrix {<br></td></tr
><tr
id=sl_svn7768_31

><td class="source"><br></td></tr
><tr
id=sl_svn7768_32

><td class="source">  public float m00, m01, m02;<br></td></tr
><tr
id=sl_svn7768_33

><td class="source">  public float m10, m11, m12;<br></td></tr
><tr
id=sl_svn7768_34

><td class="source"><br></td></tr
><tr
id=sl_svn7768_35

><td class="source"><br></td></tr
><tr
id=sl_svn7768_36

><td class="source">  public PMatrix2D() {<br></td></tr
><tr
id=sl_svn7768_37

><td class="source">    reset();<br></td></tr
><tr
id=sl_svn7768_38

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_39

><td class="source"><br></td></tr
><tr
id=sl_svn7768_40

><td class="source"><br></td></tr
><tr
id=sl_svn7768_41

><td class="source">  public PMatrix2D(float m00, float m01, float m02,<br></td></tr
><tr
id=sl_svn7768_42

><td class="source">                   float m10, float m11, float m12) {<br></td></tr
><tr
id=sl_svn7768_43

><td class="source">    set(m00, m01, m02,<br></td></tr
><tr
id=sl_svn7768_44

><td class="source">        m10, m11, m12);<br></td></tr
><tr
id=sl_svn7768_45

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_46

><td class="source"><br></td></tr
><tr
id=sl_svn7768_47

><td class="source"><br></td></tr
><tr
id=sl_svn7768_48

><td class="source">  public PMatrix2D(PMatrix matrix) {<br></td></tr
><tr
id=sl_svn7768_49

><td class="source">    set(matrix);<br></td></tr
><tr
id=sl_svn7768_50

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_51

><td class="source"><br></td></tr
><tr
id=sl_svn7768_52

><td class="source"><br></td></tr
><tr
id=sl_svn7768_53

><td class="source">  public void reset() {<br></td></tr
><tr
id=sl_svn7768_54

><td class="source">    set(1, 0, 0,<br></td></tr
><tr
id=sl_svn7768_55

><td class="source">        0, 1, 0);<br></td></tr
><tr
id=sl_svn7768_56

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_57

><td class="source"><br></td></tr
><tr
id=sl_svn7768_58

><td class="source"><br></td></tr
><tr
id=sl_svn7768_59

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_60

><td class="source">   * Returns a copy of this PMatrix.<br></td></tr
><tr
id=sl_svn7768_61

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_62

><td class="source">  public PMatrix2D get() {<br></td></tr
><tr
id=sl_svn7768_63

><td class="source">    PMatrix2D outgoing = new PMatrix2D();<br></td></tr
><tr
id=sl_svn7768_64

><td class="source">    outgoing.set(this);<br></td></tr
><tr
id=sl_svn7768_65

><td class="source">    return outgoing;<br></td></tr
><tr
id=sl_svn7768_66

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_67

><td class="source"><br></td></tr
><tr
id=sl_svn7768_68

><td class="source"><br></td></tr
><tr
id=sl_svn7768_69

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_70

><td class="source">   * Copies the matrix contents into a 6 entry float array.<br></td></tr
><tr
id=sl_svn7768_71

><td class="source">   * If target is null (or not the correct size), a new array will be created.<br></td></tr
><tr
id=sl_svn7768_72

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_73

><td class="source">  public float[] get(float[] target) {<br></td></tr
><tr
id=sl_svn7768_74

><td class="source">    if ((target == null) || (target.length != 6)) {<br></td></tr
><tr
id=sl_svn7768_75

><td class="source">      target = new float[6];<br></td></tr
><tr
id=sl_svn7768_76

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_77

><td class="source">    target[0] = m00;<br></td></tr
><tr
id=sl_svn7768_78

><td class="source">    target[1] = m01;<br></td></tr
><tr
id=sl_svn7768_79

><td class="source">    target[2] = m02;<br></td></tr
><tr
id=sl_svn7768_80

><td class="source"><br></td></tr
><tr
id=sl_svn7768_81

><td class="source">    target[3] = m10;<br></td></tr
><tr
id=sl_svn7768_82

><td class="source">    target[4] = m11;<br></td></tr
><tr
id=sl_svn7768_83

><td class="source">    target[5] = m12;<br></td></tr
><tr
id=sl_svn7768_84

><td class="source"><br></td></tr
><tr
id=sl_svn7768_85

><td class="source">    return target;<br></td></tr
><tr
id=sl_svn7768_86

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_87

><td class="source"><br></td></tr
><tr
id=sl_svn7768_88

><td class="source"><br></td></tr
><tr
id=sl_svn7768_89

><td class="source">  public void set(PMatrix matrix) {<br></td></tr
><tr
id=sl_svn7768_90

><td class="source">    if (matrix instanceof PMatrix2D) {<br></td></tr
><tr
id=sl_svn7768_91

><td class="source">      PMatrix2D src = (PMatrix2D) matrix;<br></td></tr
><tr
id=sl_svn7768_92

><td class="source">      set(src.m00, src.m01, src.m02,<br></td></tr
><tr
id=sl_svn7768_93

><td class="source">          src.m10, src.m11, src.m12);<br></td></tr
><tr
id=sl_svn7768_94

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_95

><td class="source">      throw new IllegalArgumentException(&quot;PMatrix2D.set() only accepts PMatrix2D objects.&quot;);<br></td></tr
><tr
id=sl_svn7768_96

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_97

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_98

><td class="source"><br></td></tr
><tr
id=sl_svn7768_99

><td class="source"><br></td></tr
><tr
id=sl_svn7768_100

><td class="source">  public void set(PMatrix3D src) {<br></td></tr
><tr
id=sl_svn7768_101

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_102

><td class="source"><br></td></tr
><tr
id=sl_svn7768_103

><td class="source"><br></td></tr
><tr
id=sl_svn7768_104

><td class="source">  public void set(float[] source) {<br></td></tr
><tr
id=sl_svn7768_105

><td class="source">    m00 = source[0];<br></td></tr
><tr
id=sl_svn7768_106

><td class="source">    m01 = source[1];<br></td></tr
><tr
id=sl_svn7768_107

><td class="source">    m02 = source[2];<br></td></tr
><tr
id=sl_svn7768_108

><td class="source"><br></td></tr
><tr
id=sl_svn7768_109

><td class="source">    m10 = source[3];<br></td></tr
><tr
id=sl_svn7768_110

><td class="source">    m11 = source[4];<br></td></tr
><tr
id=sl_svn7768_111

><td class="source">    m12 = source[5];<br></td></tr
><tr
id=sl_svn7768_112

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_113

><td class="source"><br></td></tr
><tr
id=sl_svn7768_114

><td class="source"><br></td></tr
><tr
id=sl_svn7768_115

><td class="source">  public void set(float m00, float m01, float m02,<br></td></tr
><tr
id=sl_svn7768_116

><td class="source">                  float m10, float m11, float m12) {<br></td></tr
><tr
id=sl_svn7768_117

><td class="source">    this.m00 = m00; this.m01 = m01; this.m02 = m02;<br></td></tr
><tr
id=sl_svn7768_118

><td class="source">    this.m10 = m10; this.m11 = m11; this.m12 = m12;<br></td></tr
><tr
id=sl_svn7768_119

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_120

><td class="source"><br></td></tr
><tr
id=sl_svn7768_121

><td class="source"><br></td></tr
><tr
id=sl_svn7768_122

><td class="source">  public void set(float m00, float m01, float m02, float m03,<br></td></tr
><tr
id=sl_svn7768_123

><td class="source">                  float m10, float m11, float m12, float m13,<br></td></tr
><tr
id=sl_svn7768_124

><td class="source">                  float m20, float m21, float m22, float m23,<br></td></tr
><tr
id=sl_svn7768_125

><td class="source">                  float m30, float m31, float m32, float m33) {<br></td></tr
><tr
id=sl_svn7768_126

><td class="source"><br></td></tr
><tr
id=sl_svn7768_127

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_128

><td class="source"><br></td></tr
><tr
id=sl_svn7768_129

><td class="source"><br></td></tr
><tr
id=sl_svn7768_130

><td class="source">  public void translate(float tx, float ty) {<br></td></tr
><tr
id=sl_svn7768_131

><td class="source">    m02 = tx*m00 + ty*m01 + m02;<br></td></tr
><tr
id=sl_svn7768_132

><td class="source">    m12 = tx*m10 + ty*m11 + m12;<br></td></tr
><tr
id=sl_svn7768_133

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_134

><td class="source"><br></td></tr
><tr
id=sl_svn7768_135

><td class="source"><br></td></tr
><tr
id=sl_svn7768_136

><td class="source">  public void translate(float x, float y, float z) {<br></td></tr
><tr
id=sl_svn7768_137

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use translate(x, y, z) on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_138

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_139

><td class="source"><br></td></tr
><tr
id=sl_svn7768_140

><td class="source"><br></td></tr
><tr
id=sl_svn7768_141

><td class="source">  // Implementation roughly based on AffineTransform.<br></td></tr
><tr
id=sl_svn7768_142

><td class="source">  public void rotate(float angle) {<br></td></tr
><tr
id=sl_svn7768_143

><td class="source">    float s = sin(angle);<br></td></tr
><tr
id=sl_svn7768_144

><td class="source">    float c = cos(angle);<br></td></tr
><tr
id=sl_svn7768_145

><td class="source"><br></td></tr
><tr
id=sl_svn7768_146

><td class="source">    float temp1 = m00;<br></td></tr
><tr
id=sl_svn7768_147

><td class="source">    float temp2 = m01;<br></td></tr
><tr
id=sl_svn7768_148

><td class="source">    m00 =  c * temp1 + s * temp2;<br></td></tr
><tr
id=sl_svn7768_149

><td class="source">    m01 = -s * temp1 + c * temp2;<br></td></tr
><tr
id=sl_svn7768_150

><td class="source">    temp1 = m10;<br></td></tr
><tr
id=sl_svn7768_151

><td class="source">    temp2 = m11;<br></td></tr
><tr
id=sl_svn7768_152

><td class="source">    m10 =  c * temp1 + s * temp2;<br></td></tr
><tr
id=sl_svn7768_153

><td class="source">    m11 = -s * temp1 + c * temp2;<br></td></tr
><tr
id=sl_svn7768_154

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_155

><td class="source"><br></td></tr
><tr
id=sl_svn7768_156

><td class="source"><br></td></tr
><tr
id=sl_svn7768_157

><td class="source">  public void rotateX(float angle) {<br></td></tr
><tr
id=sl_svn7768_158

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use rotateX() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_159

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_160

><td class="source"><br></td></tr
><tr
id=sl_svn7768_161

><td class="source"><br></td></tr
><tr
id=sl_svn7768_162

><td class="source">  public void rotateY(float angle) {<br></td></tr
><tr
id=sl_svn7768_163

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use rotateY() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_164

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_165

><td class="source"><br></td></tr
><tr
id=sl_svn7768_166

><td class="source"><br></td></tr
><tr
id=sl_svn7768_167

><td class="source">  public void rotateZ(float angle) {<br></td></tr
><tr
id=sl_svn7768_168

><td class="source">    rotate(angle);<br></td></tr
><tr
id=sl_svn7768_169

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_170

><td class="source"><br></td></tr
><tr
id=sl_svn7768_171

><td class="source"><br></td></tr
><tr
id=sl_svn7768_172

><td class="source">  public void rotate(float angle, float v0, float v1, float v2) {<br></td></tr
><tr
id=sl_svn7768_173

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use this version of rotate() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_174

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_175

><td class="source"><br></td></tr
><tr
id=sl_svn7768_176

><td class="source"><br></td></tr
><tr
id=sl_svn7768_177

><td class="source">  public void scale(float s) {<br></td></tr
><tr
id=sl_svn7768_178

><td class="source">    scale(s, s);<br></td></tr
><tr
id=sl_svn7768_179

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_180

><td class="source"><br></td></tr
><tr
id=sl_svn7768_181

><td class="source"><br></td></tr
><tr
id=sl_svn7768_182

><td class="source">  public void scale(float sx, float sy) {<br></td></tr
><tr
id=sl_svn7768_183

><td class="source">    m00 *= sx;  m01 *= sy;<br></td></tr
><tr
id=sl_svn7768_184

><td class="source">    m10 *= sx;  m11 *= sy;<br></td></tr
><tr
id=sl_svn7768_185

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_186

><td class="source"><br></td></tr
><tr
id=sl_svn7768_187

><td class="source"><br></td></tr
><tr
id=sl_svn7768_188

><td class="source">  public void scale(float x, float y, float z) {<br></td></tr
><tr
id=sl_svn7768_189

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use this version of scale() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_190

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_191

><td class="source"><br></td></tr
><tr
id=sl_svn7768_192

><td class="source"><br></td></tr
><tr
id=sl_svn7768_193

><td class="source">  public void shearX(float angle) {<br></td></tr
><tr
id=sl_svn7768_194

><td class="source">    apply(1, 0, 1,  tan(angle), 0, 0);<br></td></tr
><tr
id=sl_svn7768_195

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_196

><td class="source"><br></td></tr
><tr
id=sl_svn7768_197

><td class="source"><br></td></tr
><tr
id=sl_svn7768_198

><td class="source">  public void shearY(float angle) {<br></td></tr
><tr
id=sl_svn7768_199

><td class="source">    apply(1, 0, 1,  0, tan(angle), 0);<br></td></tr
><tr
id=sl_svn7768_200

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_201

><td class="source"><br></td></tr
><tr
id=sl_svn7768_202

><td class="source"><br></td></tr
><tr
id=sl_svn7768_203

><td class="source">  public void apply(PMatrix source) {<br></td></tr
><tr
id=sl_svn7768_204

><td class="source">    if (source instanceof PMatrix2D) {<br></td></tr
><tr
id=sl_svn7768_205

><td class="source">      apply((PMatrix2D) source);<br></td></tr
><tr
id=sl_svn7768_206

><td class="source">    } else if (source instanceof PMatrix3D) {<br></td></tr
><tr
id=sl_svn7768_207

><td class="source">      apply((PMatrix3D) source);<br></td></tr
><tr
id=sl_svn7768_208

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_209

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_210

><td class="source"><br></td></tr
><tr
id=sl_svn7768_211

><td class="source"><br></td></tr
><tr
id=sl_svn7768_212

><td class="source">  public void apply(PMatrix2D source) {<br></td></tr
><tr
id=sl_svn7768_213

><td class="source">    apply(source.m00, source.m01, source.m02,<br></td></tr
><tr
id=sl_svn7768_214

><td class="source">          source.m10, source.m11, source.m12);<br></td></tr
><tr
id=sl_svn7768_215

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_216

><td class="source"><br></td></tr
><tr
id=sl_svn7768_217

><td class="source"><br></td></tr
><tr
id=sl_svn7768_218

><td class="source">  public void apply(PMatrix3D source) {<br></td></tr
><tr
id=sl_svn7768_219

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use apply(PMatrix3D) on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_220

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_221

><td class="source"><br></td></tr
><tr
id=sl_svn7768_222

><td class="source"><br></td></tr
><tr
id=sl_svn7768_223

><td class="source">  public void apply(float n00, float n01, float n02,<br></td></tr
><tr
id=sl_svn7768_224

><td class="source">                    float n10, float n11, float n12) {<br></td></tr
><tr
id=sl_svn7768_225

><td class="source">    float t0 = m00;<br></td></tr
><tr
id=sl_svn7768_226

><td class="source">    float t1 = m01;<br></td></tr
><tr
id=sl_svn7768_227

><td class="source">    m00  = n00 * t0 + n10 * t1;<br></td></tr
><tr
id=sl_svn7768_228

><td class="source">    m01  = n01 * t0 + n11 * t1;<br></td></tr
><tr
id=sl_svn7768_229

><td class="source">    m02 += n02 * t0 + n12 * t1;<br></td></tr
><tr
id=sl_svn7768_230

><td class="source"><br></td></tr
><tr
id=sl_svn7768_231

><td class="source">    t0 = m10;<br></td></tr
><tr
id=sl_svn7768_232

><td class="source">    t1 = m11;<br></td></tr
><tr
id=sl_svn7768_233

><td class="source">    m10  = n00 * t0 + n10 * t1;<br></td></tr
><tr
id=sl_svn7768_234

><td class="source">    m11  = n01 * t0 + n11 * t1;<br></td></tr
><tr
id=sl_svn7768_235

><td class="source">    m12 += n02 * t0 + n12 * t1;<br></td></tr
><tr
id=sl_svn7768_236

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_237

><td class="source"><br></td></tr
><tr
id=sl_svn7768_238

><td class="source"><br></td></tr
><tr
id=sl_svn7768_239

><td class="source">  public void apply(float n00, float n01, float n02, float n03,<br></td></tr
><tr
id=sl_svn7768_240

><td class="source">                    float n10, float n11, float n12, float n13,<br></td></tr
><tr
id=sl_svn7768_241

><td class="source">                    float n20, float n21, float n22, float n23,<br></td></tr
><tr
id=sl_svn7768_242

><td class="source">                    float n30, float n31, float n32, float n33) {<br></td></tr
><tr
id=sl_svn7768_243

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use this version of apply() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_244

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_245

><td class="source"><br></td></tr
><tr
id=sl_svn7768_246

><td class="source"><br></td></tr
><tr
id=sl_svn7768_247

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_248

><td class="source">   * Apply another matrix to the left of this one.<br></td></tr
><tr
id=sl_svn7768_249

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_250

><td class="source">  public void preApply(PMatrix2D left) {<br></td></tr
><tr
id=sl_svn7768_251

><td class="source">    preApply(left.m00, left.m01, left.m02,<br></td></tr
><tr
id=sl_svn7768_252

><td class="source">             left.m10, left.m11, left.m12);<br></td></tr
><tr
id=sl_svn7768_253

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_254

><td class="source"><br></td></tr
><tr
id=sl_svn7768_255

><td class="source"><br></td></tr
><tr
id=sl_svn7768_256

><td class="source">  public void preApply(PMatrix3D left) {<br></td></tr
><tr
id=sl_svn7768_257

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use preApply(PMatrix3D) on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_258

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_259

><td class="source"><br></td></tr
><tr
id=sl_svn7768_260

><td class="source"><br></td></tr
><tr
id=sl_svn7768_261

><td class="source">  public void preApply(float n00, float n01, float n02,<br></td></tr
><tr
id=sl_svn7768_262

><td class="source">                       float n10, float n11, float n12) {<br></td></tr
><tr
id=sl_svn7768_263

><td class="source">    float t0 = m02;<br></td></tr
><tr
id=sl_svn7768_264

><td class="source">    float t1 = m12;<br></td></tr
><tr
id=sl_svn7768_265

><td class="source">    n02 += t0 * n00 + t1 * n01;<br></td></tr
><tr
id=sl_svn7768_266

><td class="source">    n12 += t0 * n10 + t1 * n11;<br></td></tr
><tr
id=sl_svn7768_267

><td class="source"><br></td></tr
><tr
id=sl_svn7768_268

><td class="source">    m02 = n02;<br></td></tr
><tr
id=sl_svn7768_269

><td class="source">    m12 = n12;<br></td></tr
><tr
id=sl_svn7768_270

><td class="source"><br></td></tr
><tr
id=sl_svn7768_271

><td class="source">    t0 = m00;<br></td></tr
><tr
id=sl_svn7768_272

><td class="source">    t1 = m10;<br></td></tr
><tr
id=sl_svn7768_273

><td class="source">    m00 = t0 * n00 + t1 * n01;<br></td></tr
><tr
id=sl_svn7768_274

><td class="source">    m10 = t0 * n10 + t1 * n11;<br></td></tr
><tr
id=sl_svn7768_275

><td class="source"><br></td></tr
><tr
id=sl_svn7768_276

><td class="source">    t0 = m01;<br></td></tr
><tr
id=sl_svn7768_277

><td class="source">    t1 = m11;<br></td></tr
><tr
id=sl_svn7768_278

><td class="source">    m01 = t0 * n00 + t1 * n01;<br></td></tr
><tr
id=sl_svn7768_279

><td class="source">    m11 = t0 * n10 + t1 * n11;<br></td></tr
><tr
id=sl_svn7768_280

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_281

><td class="source"><br></td></tr
><tr
id=sl_svn7768_282

><td class="source"><br></td></tr
><tr
id=sl_svn7768_283

><td class="source">  public void preApply(float n00, float n01, float n02, float n03,<br></td></tr
><tr
id=sl_svn7768_284

><td class="source">                       float n10, float n11, float n12, float n13,<br></td></tr
><tr
id=sl_svn7768_285

><td class="source">                       float n20, float n21, float n22, float n23,<br></td></tr
><tr
id=sl_svn7768_286

><td class="source">                       float n30, float n31, float n32, float n33) {<br></td></tr
><tr
id=sl_svn7768_287

><td class="source">    throw new IllegalArgumentException(&quot;Cannot use this version of preApply() on a PMatrix2D.&quot;);<br></td></tr
><tr
id=sl_svn7768_288

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_289

><td class="source"><br></td></tr
><tr
id=sl_svn7768_290

><td class="source"><br></td></tr
><tr
id=sl_svn7768_291

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_292

><td class="source"><br></td></tr
><tr
id=sl_svn7768_293

><td class="source"><br></td></tr
><tr
id=sl_svn7768_294

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_295

><td class="source">   * Multiply the x and y coordinates of a PVector against this matrix.<br></td></tr
><tr
id=sl_svn7768_296

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_297

><td class="source">  public PVector mult(PVector source, PVector target) {<br></td></tr
><tr
id=sl_svn7768_298

><td class="source">    if (target == null) {<br></td></tr
><tr
id=sl_svn7768_299

><td class="source">      target = new PVector();<br></td></tr
><tr
id=sl_svn7768_300

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_301

><td class="source">    target.x = m00*source.x + m01*source.y + m02;<br></td></tr
><tr
id=sl_svn7768_302

><td class="source">    target.y = m10*source.x + m11*source.y + m12;<br></td></tr
><tr
id=sl_svn7768_303

><td class="source">    return target;<br></td></tr
><tr
id=sl_svn7768_304

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_305

><td class="source"><br></td></tr
><tr
id=sl_svn7768_306

><td class="source"><br></td></tr
><tr
id=sl_svn7768_307

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_308

><td class="source">   * Multiply a two element vector against this matrix.<br></td></tr
><tr
id=sl_svn7768_309

><td class="source">   * If out is null or not length four, a new float array will be returned.<br></td></tr
><tr
id=sl_svn7768_310

><td class="source">   * The values for vec and out can be the same (though that&#39;s less efficient).<br></td></tr
><tr
id=sl_svn7768_311

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_312

><td class="source">  public float[] mult(float vec[], float out[]) {<br></td></tr
><tr
id=sl_svn7768_313

><td class="source">    if (out == null || out.length != 2) {<br></td></tr
><tr
id=sl_svn7768_314

><td class="source">      out = new float[2];<br></td></tr
><tr
id=sl_svn7768_315

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_316

><td class="source"><br></td></tr
><tr
id=sl_svn7768_317

><td class="source">    if (vec == out) {<br></td></tr
><tr
id=sl_svn7768_318

><td class="source">      float tx = m00*vec[0] + m01*vec[1] + m02;<br></td></tr
><tr
id=sl_svn7768_319

><td class="source">      float ty = m10*vec[0] + m11*vec[1] + m12;<br></td></tr
><tr
id=sl_svn7768_320

><td class="source"><br></td></tr
><tr
id=sl_svn7768_321

><td class="source">      out[0] = tx;<br></td></tr
><tr
id=sl_svn7768_322

><td class="source">      out[1] = ty;<br></td></tr
><tr
id=sl_svn7768_323

><td class="source"><br></td></tr
><tr
id=sl_svn7768_324

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_325

><td class="source">      out[0] = m00*vec[0] + m01*vec[1] + m02;<br></td></tr
><tr
id=sl_svn7768_326

><td class="source">      out[1] = m10*vec[0] + m11*vec[1] + m12;<br></td></tr
><tr
id=sl_svn7768_327

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_328

><td class="source"><br></td></tr
><tr
id=sl_svn7768_329

><td class="source">    return out;<br></td></tr
><tr
id=sl_svn7768_330

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_331

><td class="source"><br></td></tr
><tr
id=sl_svn7768_332

><td class="source"><br></td></tr
><tr
id=sl_svn7768_333

><td class="source">  public float multX(float x, float y) {<br></td></tr
><tr
id=sl_svn7768_334

><td class="source">    return m00*x + m01*y + m02;<br></td></tr
><tr
id=sl_svn7768_335

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_336

><td class="source"><br></td></tr
><tr
id=sl_svn7768_337

><td class="source"><br></td></tr
><tr
id=sl_svn7768_338

><td class="source">  public float multY(float x, float y) {<br></td></tr
><tr
id=sl_svn7768_339

><td class="source">    return m10*x + m11*y + m12;<br></td></tr
><tr
id=sl_svn7768_340

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_341

><td class="source"><br></td></tr
><tr
id=sl_svn7768_342

><td class="source"><br></td></tr
><tr
id=sl_svn7768_343

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_344

><td class="source">   * Transpose this matrix.<br></td></tr
><tr
id=sl_svn7768_345

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_346

><td class="source">  public void transpose() {<br></td></tr
><tr
id=sl_svn7768_347

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_348

><td class="source"><br></td></tr
><tr
id=sl_svn7768_349

><td class="source"><br></td></tr
><tr
id=sl_svn7768_350

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_351

><td class="source">   * Invert this matrix. Implementation stolen from OpenJDK.<br></td></tr
><tr
id=sl_svn7768_352

><td class="source">   * @return true if successful<br></td></tr
><tr
id=sl_svn7768_353

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_354

><td class="source">  public boolean invert() {<br></td></tr
><tr
id=sl_svn7768_355

><td class="source">    float determinant = determinant();<br></td></tr
><tr
id=sl_svn7768_356

><td class="source">    if (Math.abs(determinant) &lt;= Float.MIN_VALUE) {<br></td></tr
><tr
id=sl_svn7768_357

><td class="source">      return false;<br></td></tr
><tr
id=sl_svn7768_358

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_359

><td class="source"><br></td></tr
><tr
id=sl_svn7768_360

><td class="source">    float t00 = m00;<br></td></tr
><tr
id=sl_svn7768_361

><td class="source">    float t01 = m01;<br></td></tr
><tr
id=sl_svn7768_362

><td class="source">    float t02 = m02;<br></td></tr
><tr
id=sl_svn7768_363

><td class="source">    float t10 = m10;<br></td></tr
><tr
id=sl_svn7768_364

><td class="source">    float t11 = m11;<br></td></tr
><tr
id=sl_svn7768_365

><td class="source">    float t12 = m12;<br></td></tr
><tr
id=sl_svn7768_366

><td class="source"><br></td></tr
><tr
id=sl_svn7768_367

><td class="source">    m00 =  t11 / determinant;<br></td></tr
><tr
id=sl_svn7768_368

><td class="source">    m10 = -t10 / determinant;<br></td></tr
><tr
id=sl_svn7768_369

><td class="source">    m01 = -t01 / determinant;<br></td></tr
><tr
id=sl_svn7768_370

><td class="source">    m11 =  t00 / determinant;<br></td></tr
><tr
id=sl_svn7768_371

><td class="source">    m02 = (t01 * t12 - t11 * t02) / determinant;<br></td></tr
><tr
id=sl_svn7768_372

><td class="source">    m12 = (t10 * t02 - t00 * t12) / determinant;<br></td></tr
><tr
id=sl_svn7768_373

><td class="source"><br></td></tr
><tr
id=sl_svn7768_374

><td class="source">    return true;<br></td></tr
><tr
id=sl_svn7768_375

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_376

><td class="source"><br></td></tr
><tr
id=sl_svn7768_377

><td class="source"><br></td></tr
><tr
id=sl_svn7768_378

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_379

><td class="source">   * @return the determinant of the matrix<br></td></tr
><tr
id=sl_svn7768_380

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_381

><td class="source">  public float determinant() {<br></td></tr
><tr
id=sl_svn7768_382

><td class="source">    return m00 * m11 - m01 * m10;<br></td></tr
><tr
id=sl_svn7768_383

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_384

><td class="source"><br></td></tr
><tr
id=sl_svn7768_385

><td class="source"><br></td></tr
><tr
id=sl_svn7768_386

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_387

><td class="source"><br></td></tr
><tr
id=sl_svn7768_388

><td class="source"><br></td></tr
><tr
id=sl_svn7768_389

><td class="source">  public void print() {<br></td></tr
><tr
id=sl_svn7768_390

><td class="source">    int big = (int) abs(max(PApplet.max(abs(m00), abs(m01), abs(m02)),<br></td></tr
><tr
id=sl_svn7768_391

><td class="source">                            PApplet.max(abs(m10), abs(m11), abs(m12))));<br></td></tr
><tr
id=sl_svn7768_392

><td class="source"><br></td></tr
><tr
id=sl_svn7768_393

><td class="source">    int digits = 1;<br></td></tr
><tr
id=sl_svn7768_394

><td class="source">    if (Float.isNaN(big) || Float.isInfinite(big)) {  // avoid infinite loop<br></td></tr
><tr
id=sl_svn7768_395

><td class="source">      digits = 5;<br></td></tr
><tr
id=sl_svn7768_396

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_397

><td class="source">      while ((big /= 10) != 0) digits++;  // cheap log()<br></td></tr
><tr
id=sl_svn7768_398

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_399

><td class="source"><br></td></tr
><tr
id=sl_svn7768_400

><td class="source">    System.out.println(PApplet.nfs(m00, digits, 4) + &quot; &quot; +<br></td></tr
><tr
id=sl_svn7768_401

><td class="source">                       PApplet.nfs(m01, digits, 4) + &quot; &quot; +<br></td></tr
><tr
id=sl_svn7768_402

><td class="source">                       PApplet.nfs(m02, digits, 4));<br></td></tr
><tr
id=sl_svn7768_403

><td class="source"><br></td></tr
><tr
id=sl_svn7768_404

><td class="source">    System.out.println(PApplet.nfs(m10, digits, 4) + &quot; &quot; +<br></td></tr
><tr
id=sl_svn7768_405

><td class="source">                       PApplet.nfs(m11, digits, 4) + &quot; &quot; +<br></td></tr
><tr
id=sl_svn7768_406

><td class="source">                       PApplet.nfs(m12, digits, 4));<br></td></tr
><tr
id=sl_svn7768_407

><td class="source"><br></td></tr
><tr
id=sl_svn7768_408

><td class="source">    System.out.println();<br></td></tr
><tr
id=sl_svn7768_409

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_410

><td class="source"><br></td></tr
><tr
id=sl_svn7768_411

><td class="source"><br></td></tr
><tr
id=sl_svn7768_412

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_413

><td class="source"><br></td></tr
><tr
id=sl_svn7768_414

><td class="source">  // TODO these need to be added as regular API, but the naming and <br></td></tr
><tr
id=sl_svn7768_415

><td class="source">  // implementation needs to be improved first. (e.g. actually keeping track<br></td></tr
><tr
id=sl_svn7768_416

><td class="source">  // of whether the matrix is in fact identity internally.)<br></td></tr
><tr
id=sl_svn7768_417

><td class="source"><br></td></tr
><tr
id=sl_svn7768_418

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_419

><td class="source">  protected boolean isIdentity() {<br></td></tr
><tr
id=sl_svn7768_420

><td class="source">    return ((m00 == 1) &amp;&amp; (m01 == 0) &amp;&amp; (m02 == 0) &amp;&amp;<br></td></tr
><tr
id=sl_svn7768_421

><td class="source">            (m10 == 0) &amp;&amp; (m11 == 1) &amp;&amp; (m12 == 0));<br></td></tr
><tr
id=sl_svn7768_422

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_423

><td class="source"><br></td></tr
><tr
id=sl_svn7768_424

><td class="source"><br></td></tr
><tr
id=sl_svn7768_425

><td class="source">  // TODO make this more efficient, or move into PMatrix2D<br></td></tr
><tr
id=sl_svn7768_426

><td class="source">  protected boolean isWarped() {<br></td></tr
><tr
id=sl_svn7768_427

><td class="source">    return ((m00 != 1) || (m01 != 0) &amp;&amp; <br></td></tr
><tr
id=sl_svn7768_428

><td class="source">            (m10 != 0) || (m11 != 1));<br></td></tr
><tr
id=sl_svn7768_429

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_430

><td class="source"><br></td></tr
><tr
id=sl_svn7768_431

><td class="source"><br></td></tr
><tr
id=sl_svn7768_432

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_433

><td class="source"><br></td></tr
><tr
id=sl_svn7768_434

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_435

><td class="source">  private final float max(float a, float b) {<br></td></tr
><tr
id=sl_svn7768_436

><td class="source">    return (a &gt; b) ? a : b;<br></td></tr
><tr
id=sl_svn7768_437

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_438

><td class="source"><br></td></tr
><tr
id=sl_svn7768_439

><td class="source">  private final float abs(float a) {<br></td></tr
><tr
id=sl_svn7768_440

><td class="source">    return (a &lt; 0) ? -a : a;<br></td></tr
><tr
id=sl_svn7768_441

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_442

><td class="source"><br></td></tr
><tr
id=sl_svn7768_443

><td class="source">  private final float sin(float angle) {<br></td></tr
><tr
id=sl_svn7768_444

><td class="source">    return (float)Math.sin(angle);<br></td></tr
><tr
id=sl_svn7768_445

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_446

><td class="source"><br></td></tr
><tr
id=sl_svn7768_447

><td class="source">  private final float cos(float angle) {<br></td></tr
><tr
id=sl_svn7768_448

><td class="source">    return (float)Math.cos(angle);<br></td></tr
><tr
id=sl_svn7768_449

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_450

><td class="source"><br></td></tr
><tr
id=sl_svn7768_451

><td class="source">  private final float tan(float angle) {<br></td></tr
><tr
id=sl_svn7768_452

><td class="source">    return (float)Math.tan(angle);<br></td></tr
><tr
id=sl_svn7768_453

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_454

><td class="source">}<br></td></tr
></table></pre>
<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn7768_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn7768_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta('', 'p', 'processing', this)">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta('', 'p', 'processing', this)">Hide details</a>
 </div>
 <div class="ifExpand">
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/processing/source/detail?spec=svn7768&r=7133">r7133</a>
 by f...@processing.org
 on Jul 18, 2010
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7133&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old_path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old=6524">Diff</a>
 </div>
 <pre>change skewX/Y to shearX/Y</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/processing/source/detail?r=7133&spec=svn7768';
 var publish_url = '/p/processing/source/detail?r=7133&spec=svn7768#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PApplet.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PApplet.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PGraphics.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphics.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PGraphicsAndroid2D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphicsAndroid2D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PGraphicsAndroid3D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphicsAndroid3D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PMatrix.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PMatrix2D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix2D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/core/src/processing/core/PMatrix3D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix3D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/android/todo.txt');
 changed_urls.push('/p/processing/source/browse/trunk/processing/android/todo.txt?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PApplet.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PApplet.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PGraphics.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PGraphics3D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics3D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PMatrix.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PMatrix2D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix2D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 var selected_path = '/trunk/processing/core/src/processing/core/PMatrix2D.java';
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PMatrix3D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix3D.java?r\x3d7133\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/todo.txt');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/todo.txt?r\x3d7133\x26spec\x3dsvn7768');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PApplet.java?r=7133&amp;spec=svn7768"
 
 >...src/processing/core/PApplet.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphics.java?r=7133&amp;spec=svn7768"
 
 >...c/processing/core/PGraphics.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphicsAndroid2D.java?r=7133&amp;spec=svn7768"
 
 >...ing/core/PGraphicsAndroid2D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PGraphicsAndroid3D.java?r=7133&amp;spec=svn7768"
 
 >...ing/core/PGraphicsAndroid3D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix.java?r=7133&amp;spec=svn7768"
 
 >...src/processing/core/PMatrix.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix2D.java?r=7133&amp;spec=svn7768"
 
 >...c/processing/core/PMatrix2D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/core/src/processing/core/PMatrix3D.java?r=7133&amp;spec=svn7768"
 
 >...c/processing/core/PMatrix3D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/android/todo.txt?r=7133&amp;spec=svn7768"
 
 >/trunk/processing/android/todo.txt</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PApplet.java?r=7133&amp;spec=svn7768"
 
 >...src/processing/core/PApplet.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics.java?r=7133&amp;spec=svn7768"
 
 >...c/processing/core/PGraphics.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics3D.java?r=7133&amp;spec=svn7768"
 
 >...processing/core/PGraphics3D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix.java?r=7133&amp;spec=svn7768"
 
 >...src/processing/core/PMatrix.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix2D.java?r=7133&amp;spec=svn7768"
 selected="selected"
 >...c/processing/core/PMatrix2D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMatrix3D.java?r=7133&amp;spec=svn7768"
 
 >...c/processing/core/PMatrix3D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/todo.txt?r=7133&amp;spec=svn7768"
 
 >/trunk/processing/core/todo.txt</option>
 
 </select>
 </td></tr></table>
 
 
 



 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=6524">r6524</a>
 by fry
 on Mar 23, 2010
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=6524&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old_path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old=5141">Diff</a>
 <br>
 <pre class="ifOpened">added skewX/Y (bug #1448) and fixed
bugs in its implementation
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=5141">r5141</a>
 by fry
 on Nov 18, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=5141&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old_path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old=4997">Diff</a>
 <br>
 <pre class="ifOpened">major work to bring back P2D... so far
rect() set up properly, now dealing
with begin/endShape issues
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=4997">r4997</a>
 by fry
 on Oct 21, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=4997&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old_path=/trunk/processing/core/src/processing/core/PMatrix2D.java&amp;old=4731">Diff</a>
 <br>
 <pre class="ifOpened">adding style attributes for svg, also
fix the spacing in the file
</pre>
 </div>
 
 
 <a href="/p/processing/source/list?path=/trunk/processing/core/src/processing/core/PMatrix2D.java&start=7133">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 10804 bytes,
 454 lines</div>
 
 <div><a href="http://processing.googlecode.com/svn/trunk/processing/core/src/processing/core/PMatrix2D.java">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>

<script src="http://www.gstatic.com/codesite/ph/10276742928614796628/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


<script src="http://www.gstatic.com/codesite/ph/10276742928614796628/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="https://kibbles.googlecode.com/files/kibbles-1.3.3.comp.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initilized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initilized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="http://www.gstatic.com/codesite/ph/10276742928614796628/js/code_review_scripts.js"></script>
<script type="text/javascript">
 
 // the comment form template
 var form = '<div class="draft"><div class="header"><span class="title">Draft comment:</span></div>' +
 '<div class="body"><form onsubmit="return false;"><textarea id="$ID">$BODY</textarea><br>$ACTIONS</form></div>' +
 '</div>';
 // the comment "plate" template used for both draft and published comment "plates".
 var draft_comment = '<div class="draft" ondblclick="$ONDBLCLICK">' +
 '<div class="header"><span class="title">Draft comment:</span><span class="actions">$ACTIONS</span></div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';
 var published_comment = '<div class="published">' +
 '<div class="header"><span class="title"><a href="$PROFILE_URL">$AUTHOR:</a></span><div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';

 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn7768': '/trunk/processing/core/src/processing/core/PMatrix2D.java'}
 CR_setup('', 'p', 'processing', '', 'svn7768', paths,
 'c6974bcd72eb95455827185f7306e1fa', CR_BrowseIntegrationFactory);
 // register our hidden ui elements with the code commenting code ui builder.
 CR_registerLayoutElement('form', form);
 CR_registerLayoutElement('draft_comment', draft_comment);
 CR_registerLayoutElement('published_comment', published_comment);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_PUB_PLATE, pubRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, draftRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initilized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/10276742928614796628/js/dit_scripts.js"></script>

 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/10276742928614796628/js/core_scripts_20081103.js"></script>
 <script type="text/javascript" src="/js/codesite_product_dictionary_ph.pack.04102009.js"></script>
</div> 
<div id="footer" dir="ltr">
 
 <div class="text">
 
 &copy;2010 Google -
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>
 
 


 
 
 <script type="text/javascript">_CS_reportToCsi();</script>
 
 </body>
</html>

