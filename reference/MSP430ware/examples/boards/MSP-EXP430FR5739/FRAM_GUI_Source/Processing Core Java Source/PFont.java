



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 
 
 var codesite_token = "c6974bcd72eb95455827185f7306e1fa";
 
 
 var logged_in_user_email = "Dung.Dang@gmail.com";
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>PFont.java - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fprocessing%2Fsource%2Fbrowse%2Ftrunk%2Fprocessing%2Fcore%2Fsrc%2Fprocessing%2Fcore%2FPFont.java" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/processing/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/">core</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/">src</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/">core</a><span class="sp">/&nbsp;</span>PFont.java</span>
 
 

 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PFont.java?edit=1"
 ><img src="http://www.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PFont.java?r=7647" title="Previous">&lsaquo;r7647</a></li>
 
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
><tr id="gr_svn7768_455"

><td id="455"><a href="#455">455</a></td></tr
><tr id="gr_svn7768_456"

><td id="456"><a href="#456">456</a></td></tr
><tr id="gr_svn7768_457"

><td id="457"><a href="#457">457</a></td></tr
><tr id="gr_svn7768_458"

><td id="458"><a href="#458">458</a></td></tr
><tr id="gr_svn7768_459"

><td id="459"><a href="#459">459</a></td></tr
><tr id="gr_svn7768_460"

><td id="460"><a href="#460">460</a></td></tr
><tr id="gr_svn7768_461"

><td id="461"><a href="#461">461</a></td></tr
><tr id="gr_svn7768_462"

><td id="462"><a href="#462">462</a></td></tr
><tr id="gr_svn7768_463"

><td id="463"><a href="#463">463</a></td></tr
><tr id="gr_svn7768_464"

><td id="464"><a href="#464">464</a></td></tr
><tr id="gr_svn7768_465"

><td id="465"><a href="#465">465</a></td></tr
><tr id="gr_svn7768_466"

><td id="466"><a href="#466">466</a></td></tr
><tr id="gr_svn7768_467"

><td id="467"><a href="#467">467</a></td></tr
><tr id="gr_svn7768_468"

><td id="468"><a href="#468">468</a></td></tr
><tr id="gr_svn7768_469"

><td id="469"><a href="#469">469</a></td></tr
><tr id="gr_svn7768_470"

><td id="470"><a href="#470">470</a></td></tr
><tr id="gr_svn7768_471"

><td id="471"><a href="#471">471</a></td></tr
><tr id="gr_svn7768_472"

><td id="472"><a href="#472">472</a></td></tr
><tr id="gr_svn7768_473"

><td id="473"><a href="#473">473</a></td></tr
><tr id="gr_svn7768_474"

><td id="474"><a href="#474">474</a></td></tr
><tr id="gr_svn7768_475"

><td id="475"><a href="#475">475</a></td></tr
><tr id="gr_svn7768_476"

><td id="476"><a href="#476">476</a></td></tr
><tr id="gr_svn7768_477"

><td id="477"><a href="#477">477</a></td></tr
><tr id="gr_svn7768_478"

><td id="478"><a href="#478">478</a></td></tr
><tr id="gr_svn7768_479"

><td id="479"><a href="#479">479</a></td></tr
><tr id="gr_svn7768_480"

><td id="480"><a href="#480">480</a></td></tr
><tr id="gr_svn7768_481"

><td id="481"><a href="#481">481</a></td></tr
><tr id="gr_svn7768_482"

><td id="482"><a href="#482">482</a></td></tr
><tr id="gr_svn7768_483"

><td id="483"><a href="#483">483</a></td></tr
><tr id="gr_svn7768_484"

><td id="484"><a href="#484">484</a></td></tr
><tr id="gr_svn7768_485"

><td id="485"><a href="#485">485</a></td></tr
><tr id="gr_svn7768_486"

><td id="486"><a href="#486">486</a></td></tr
><tr id="gr_svn7768_487"

><td id="487"><a href="#487">487</a></td></tr
><tr id="gr_svn7768_488"

><td id="488"><a href="#488">488</a></td></tr
><tr id="gr_svn7768_489"

><td id="489"><a href="#489">489</a></td></tr
><tr id="gr_svn7768_490"

><td id="490"><a href="#490">490</a></td></tr
><tr id="gr_svn7768_491"

><td id="491"><a href="#491">491</a></td></tr
><tr id="gr_svn7768_492"

><td id="492"><a href="#492">492</a></td></tr
><tr id="gr_svn7768_493"

><td id="493"><a href="#493">493</a></td></tr
><tr id="gr_svn7768_494"

><td id="494"><a href="#494">494</a></td></tr
><tr id="gr_svn7768_495"

><td id="495"><a href="#495">495</a></td></tr
><tr id="gr_svn7768_496"

><td id="496"><a href="#496">496</a></td></tr
><tr id="gr_svn7768_497"

><td id="497"><a href="#497">497</a></td></tr
><tr id="gr_svn7768_498"

><td id="498"><a href="#498">498</a></td></tr
><tr id="gr_svn7768_499"

><td id="499"><a href="#499">499</a></td></tr
><tr id="gr_svn7768_500"

><td id="500"><a href="#500">500</a></td></tr
><tr id="gr_svn7768_501"

><td id="501"><a href="#501">501</a></td></tr
><tr id="gr_svn7768_502"

><td id="502"><a href="#502">502</a></td></tr
><tr id="gr_svn7768_503"

><td id="503"><a href="#503">503</a></td></tr
><tr id="gr_svn7768_504"

><td id="504"><a href="#504">504</a></td></tr
><tr id="gr_svn7768_505"

><td id="505"><a href="#505">505</a></td></tr
><tr id="gr_svn7768_506"

><td id="506"><a href="#506">506</a></td></tr
><tr id="gr_svn7768_507"

><td id="507"><a href="#507">507</a></td></tr
><tr id="gr_svn7768_508"

><td id="508"><a href="#508">508</a></td></tr
><tr id="gr_svn7768_509"

><td id="509"><a href="#509">509</a></td></tr
><tr id="gr_svn7768_510"

><td id="510"><a href="#510">510</a></td></tr
><tr id="gr_svn7768_511"

><td id="511"><a href="#511">511</a></td></tr
><tr id="gr_svn7768_512"

><td id="512"><a href="#512">512</a></td></tr
><tr id="gr_svn7768_513"

><td id="513"><a href="#513">513</a></td></tr
><tr id="gr_svn7768_514"

><td id="514"><a href="#514">514</a></td></tr
><tr id="gr_svn7768_515"

><td id="515"><a href="#515">515</a></td></tr
><tr id="gr_svn7768_516"

><td id="516"><a href="#516">516</a></td></tr
><tr id="gr_svn7768_517"

><td id="517"><a href="#517">517</a></td></tr
><tr id="gr_svn7768_518"

><td id="518"><a href="#518">518</a></td></tr
><tr id="gr_svn7768_519"

><td id="519"><a href="#519">519</a></td></tr
><tr id="gr_svn7768_520"

><td id="520"><a href="#520">520</a></td></tr
><tr id="gr_svn7768_521"

><td id="521"><a href="#521">521</a></td></tr
><tr id="gr_svn7768_522"

><td id="522"><a href="#522">522</a></td></tr
><tr id="gr_svn7768_523"

><td id="523"><a href="#523">523</a></td></tr
><tr id="gr_svn7768_524"

><td id="524"><a href="#524">524</a></td></tr
><tr id="gr_svn7768_525"

><td id="525"><a href="#525">525</a></td></tr
><tr id="gr_svn7768_526"

><td id="526"><a href="#526">526</a></td></tr
><tr id="gr_svn7768_527"

><td id="527"><a href="#527">527</a></td></tr
><tr id="gr_svn7768_528"

><td id="528"><a href="#528">528</a></td></tr
><tr id="gr_svn7768_529"

><td id="529"><a href="#529">529</a></td></tr
><tr id="gr_svn7768_530"

><td id="530"><a href="#530">530</a></td></tr
><tr id="gr_svn7768_531"

><td id="531"><a href="#531">531</a></td></tr
><tr id="gr_svn7768_532"

><td id="532"><a href="#532">532</a></td></tr
><tr id="gr_svn7768_533"

><td id="533"><a href="#533">533</a></td></tr
><tr id="gr_svn7768_534"

><td id="534"><a href="#534">534</a></td></tr
><tr id="gr_svn7768_535"

><td id="535"><a href="#535">535</a></td></tr
><tr id="gr_svn7768_536"

><td id="536"><a href="#536">536</a></td></tr
><tr id="gr_svn7768_537"

><td id="537"><a href="#537">537</a></td></tr
><tr id="gr_svn7768_538"

><td id="538"><a href="#538">538</a></td></tr
><tr id="gr_svn7768_539"

><td id="539"><a href="#539">539</a></td></tr
><tr id="gr_svn7768_540"

><td id="540"><a href="#540">540</a></td></tr
><tr id="gr_svn7768_541"

><td id="541"><a href="#541">541</a></td></tr
><tr id="gr_svn7768_542"

><td id="542"><a href="#542">542</a></td></tr
><tr id="gr_svn7768_543"

><td id="543"><a href="#543">543</a></td></tr
><tr id="gr_svn7768_544"

><td id="544"><a href="#544">544</a></td></tr
><tr id="gr_svn7768_545"

><td id="545"><a href="#545">545</a></td></tr
><tr id="gr_svn7768_546"

><td id="546"><a href="#546">546</a></td></tr
><tr id="gr_svn7768_547"

><td id="547"><a href="#547">547</a></td></tr
><tr id="gr_svn7768_548"

><td id="548"><a href="#548">548</a></td></tr
><tr id="gr_svn7768_549"

><td id="549"><a href="#549">549</a></td></tr
><tr id="gr_svn7768_550"

><td id="550"><a href="#550">550</a></td></tr
><tr id="gr_svn7768_551"

><td id="551"><a href="#551">551</a></td></tr
><tr id="gr_svn7768_552"

><td id="552"><a href="#552">552</a></td></tr
><tr id="gr_svn7768_553"

><td id="553"><a href="#553">553</a></td></tr
><tr id="gr_svn7768_554"

><td id="554"><a href="#554">554</a></td></tr
><tr id="gr_svn7768_555"

><td id="555"><a href="#555">555</a></td></tr
><tr id="gr_svn7768_556"

><td id="556"><a href="#556">556</a></td></tr
><tr id="gr_svn7768_557"

><td id="557"><a href="#557">557</a></td></tr
><tr id="gr_svn7768_558"

><td id="558"><a href="#558">558</a></td></tr
><tr id="gr_svn7768_559"

><td id="559"><a href="#559">559</a></td></tr
><tr id="gr_svn7768_560"

><td id="560"><a href="#560">560</a></td></tr
><tr id="gr_svn7768_561"

><td id="561"><a href="#561">561</a></td></tr
><tr id="gr_svn7768_562"

><td id="562"><a href="#562">562</a></td></tr
><tr id="gr_svn7768_563"

><td id="563"><a href="#563">563</a></td></tr
><tr id="gr_svn7768_564"

><td id="564"><a href="#564">564</a></td></tr
><tr id="gr_svn7768_565"

><td id="565"><a href="#565">565</a></td></tr
><tr id="gr_svn7768_566"

><td id="566"><a href="#566">566</a></td></tr
><tr id="gr_svn7768_567"

><td id="567"><a href="#567">567</a></td></tr
><tr id="gr_svn7768_568"

><td id="568"><a href="#568">568</a></td></tr
><tr id="gr_svn7768_569"

><td id="569"><a href="#569">569</a></td></tr
><tr id="gr_svn7768_570"

><td id="570"><a href="#570">570</a></td></tr
><tr id="gr_svn7768_571"

><td id="571"><a href="#571">571</a></td></tr
><tr id="gr_svn7768_572"

><td id="572"><a href="#572">572</a></td></tr
><tr id="gr_svn7768_573"

><td id="573"><a href="#573">573</a></td></tr
><tr id="gr_svn7768_574"

><td id="574"><a href="#574">574</a></td></tr
><tr id="gr_svn7768_575"

><td id="575"><a href="#575">575</a></td></tr
><tr id="gr_svn7768_576"

><td id="576"><a href="#576">576</a></td></tr
><tr id="gr_svn7768_577"

><td id="577"><a href="#577">577</a></td></tr
><tr id="gr_svn7768_578"

><td id="578"><a href="#578">578</a></td></tr
><tr id="gr_svn7768_579"

><td id="579"><a href="#579">579</a></td></tr
><tr id="gr_svn7768_580"

><td id="580"><a href="#580">580</a></td></tr
><tr id="gr_svn7768_581"

><td id="581"><a href="#581">581</a></td></tr
><tr id="gr_svn7768_582"

><td id="582"><a href="#582">582</a></td></tr
><tr id="gr_svn7768_583"

><td id="583"><a href="#583">583</a></td></tr
><tr id="gr_svn7768_584"

><td id="584"><a href="#584">584</a></td></tr
><tr id="gr_svn7768_585"

><td id="585"><a href="#585">585</a></td></tr
><tr id="gr_svn7768_586"

><td id="586"><a href="#586">586</a></td></tr
><tr id="gr_svn7768_587"

><td id="587"><a href="#587">587</a></td></tr
><tr id="gr_svn7768_588"

><td id="588"><a href="#588">588</a></td></tr
><tr id="gr_svn7768_589"

><td id="589"><a href="#589">589</a></td></tr
><tr id="gr_svn7768_590"

><td id="590"><a href="#590">590</a></td></tr
><tr id="gr_svn7768_591"

><td id="591"><a href="#591">591</a></td></tr
><tr id="gr_svn7768_592"

><td id="592"><a href="#592">592</a></td></tr
><tr id="gr_svn7768_593"

><td id="593"><a href="#593">593</a></td></tr
><tr id="gr_svn7768_594"

><td id="594"><a href="#594">594</a></td></tr
><tr id="gr_svn7768_595"

><td id="595"><a href="#595">595</a></td></tr
><tr id="gr_svn7768_596"

><td id="596"><a href="#596">596</a></td></tr
><tr id="gr_svn7768_597"

><td id="597"><a href="#597">597</a></td></tr
><tr id="gr_svn7768_598"

><td id="598"><a href="#598">598</a></td></tr
><tr id="gr_svn7768_599"

><td id="599"><a href="#599">599</a></td></tr
><tr id="gr_svn7768_600"

><td id="600"><a href="#600">600</a></td></tr
><tr id="gr_svn7768_601"

><td id="601"><a href="#601">601</a></td></tr
><tr id="gr_svn7768_602"

><td id="602"><a href="#602">602</a></td></tr
><tr id="gr_svn7768_603"

><td id="603"><a href="#603">603</a></td></tr
><tr id="gr_svn7768_604"

><td id="604"><a href="#604">604</a></td></tr
><tr id="gr_svn7768_605"

><td id="605"><a href="#605">605</a></td></tr
><tr id="gr_svn7768_606"

><td id="606"><a href="#606">606</a></td></tr
><tr id="gr_svn7768_607"

><td id="607"><a href="#607">607</a></td></tr
><tr id="gr_svn7768_608"

><td id="608"><a href="#608">608</a></td></tr
><tr id="gr_svn7768_609"

><td id="609"><a href="#609">609</a></td></tr
><tr id="gr_svn7768_610"

><td id="610"><a href="#610">610</a></td></tr
><tr id="gr_svn7768_611"

><td id="611"><a href="#611">611</a></td></tr
><tr id="gr_svn7768_612"

><td id="612"><a href="#612">612</a></td></tr
><tr id="gr_svn7768_613"

><td id="613"><a href="#613">613</a></td></tr
><tr id="gr_svn7768_614"

><td id="614"><a href="#614">614</a></td></tr
><tr id="gr_svn7768_615"

><td id="615"><a href="#615">615</a></td></tr
><tr id="gr_svn7768_616"

><td id="616"><a href="#616">616</a></td></tr
><tr id="gr_svn7768_617"

><td id="617"><a href="#617">617</a></td></tr
><tr id="gr_svn7768_618"

><td id="618"><a href="#618">618</a></td></tr
><tr id="gr_svn7768_619"

><td id="619"><a href="#619">619</a></td></tr
><tr id="gr_svn7768_620"

><td id="620"><a href="#620">620</a></td></tr
><tr id="gr_svn7768_621"

><td id="621"><a href="#621">621</a></td></tr
><tr id="gr_svn7768_622"

><td id="622"><a href="#622">622</a></td></tr
><tr id="gr_svn7768_623"

><td id="623"><a href="#623">623</a></td></tr
><tr id="gr_svn7768_624"

><td id="624"><a href="#624">624</a></td></tr
><tr id="gr_svn7768_625"

><td id="625"><a href="#625">625</a></td></tr
><tr id="gr_svn7768_626"

><td id="626"><a href="#626">626</a></td></tr
><tr id="gr_svn7768_627"

><td id="627"><a href="#627">627</a></td></tr
><tr id="gr_svn7768_628"

><td id="628"><a href="#628">628</a></td></tr
><tr id="gr_svn7768_629"

><td id="629"><a href="#629">629</a></td></tr
><tr id="gr_svn7768_630"

><td id="630"><a href="#630">630</a></td></tr
><tr id="gr_svn7768_631"

><td id="631"><a href="#631">631</a></td></tr
><tr id="gr_svn7768_632"

><td id="632"><a href="#632">632</a></td></tr
><tr id="gr_svn7768_633"

><td id="633"><a href="#633">633</a></td></tr
><tr id="gr_svn7768_634"

><td id="634"><a href="#634">634</a></td></tr
><tr id="gr_svn7768_635"

><td id="635"><a href="#635">635</a></td></tr
><tr id="gr_svn7768_636"

><td id="636"><a href="#636">636</a></td></tr
><tr id="gr_svn7768_637"

><td id="637"><a href="#637">637</a></td></tr
><tr id="gr_svn7768_638"

><td id="638"><a href="#638">638</a></td></tr
><tr id="gr_svn7768_639"

><td id="639"><a href="#639">639</a></td></tr
><tr id="gr_svn7768_640"

><td id="640"><a href="#640">640</a></td></tr
><tr id="gr_svn7768_641"

><td id="641"><a href="#641">641</a></td></tr
><tr id="gr_svn7768_642"

><td id="642"><a href="#642">642</a></td></tr
><tr id="gr_svn7768_643"

><td id="643"><a href="#643">643</a></td></tr
><tr id="gr_svn7768_644"

><td id="644"><a href="#644">644</a></td></tr
><tr id="gr_svn7768_645"

><td id="645"><a href="#645">645</a></td></tr
><tr id="gr_svn7768_646"

><td id="646"><a href="#646">646</a></td></tr
><tr id="gr_svn7768_647"

><td id="647"><a href="#647">647</a></td></tr
><tr id="gr_svn7768_648"

><td id="648"><a href="#648">648</a></td></tr
><tr id="gr_svn7768_649"

><td id="649"><a href="#649">649</a></td></tr
><tr id="gr_svn7768_650"

><td id="650"><a href="#650">650</a></td></tr
><tr id="gr_svn7768_651"

><td id="651"><a href="#651">651</a></td></tr
><tr id="gr_svn7768_652"

><td id="652"><a href="#652">652</a></td></tr
><tr id="gr_svn7768_653"

><td id="653"><a href="#653">653</a></td></tr
><tr id="gr_svn7768_654"

><td id="654"><a href="#654">654</a></td></tr
><tr id="gr_svn7768_655"

><td id="655"><a href="#655">655</a></td></tr
><tr id="gr_svn7768_656"

><td id="656"><a href="#656">656</a></td></tr
><tr id="gr_svn7768_657"

><td id="657"><a href="#657">657</a></td></tr
><tr id="gr_svn7768_658"

><td id="658"><a href="#658">658</a></td></tr
><tr id="gr_svn7768_659"

><td id="659"><a href="#659">659</a></td></tr
><tr id="gr_svn7768_660"

><td id="660"><a href="#660">660</a></td></tr
><tr id="gr_svn7768_661"

><td id="661"><a href="#661">661</a></td></tr
><tr id="gr_svn7768_662"

><td id="662"><a href="#662">662</a></td></tr
><tr id="gr_svn7768_663"

><td id="663"><a href="#663">663</a></td></tr
><tr id="gr_svn7768_664"

><td id="664"><a href="#664">664</a></td></tr
><tr id="gr_svn7768_665"

><td id="665"><a href="#665">665</a></td></tr
><tr id="gr_svn7768_666"

><td id="666"><a href="#666">666</a></td></tr
><tr id="gr_svn7768_667"

><td id="667"><a href="#667">667</a></td></tr
><tr id="gr_svn7768_668"

><td id="668"><a href="#668">668</a></td></tr
><tr id="gr_svn7768_669"

><td id="669"><a href="#669">669</a></td></tr
><tr id="gr_svn7768_670"

><td id="670"><a href="#670">670</a></td></tr
><tr id="gr_svn7768_671"

><td id="671"><a href="#671">671</a></td></tr
><tr id="gr_svn7768_672"

><td id="672"><a href="#672">672</a></td></tr
><tr id="gr_svn7768_673"

><td id="673"><a href="#673">673</a></td></tr
><tr id="gr_svn7768_674"

><td id="674"><a href="#674">674</a></td></tr
><tr id="gr_svn7768_675"

><td id="675"><a href="#675">675</a></td></tr
><tr id="gr_svn7768_676"

><td id="676"><a href="#676">676</a></td></tr
><tr id="gr_svn7768_677"

><td id="677"><a href="#677">677</a></td></tr
><tr id="gr_svn7768_678"

><td id="678"><a href="#678">678</a></td></tr
><tr id="gr_svn7768_679"

><td id="679"><a href="#679">679</a></td></tr
><tr id="gr_svn7768_680"

><td id="680"><a href="#680">680</a></td></tr
><tr id="gr_svn7768_681"

><td id="681"><a href="#681">681</a></td></tr
><tr id="gr_svn7768_682"

><td id="682"><a href="#682">682</a></td></tr
><tr id="gr_svn7768_683"

><td id="683"><a href="#683">683</a></td></tr
><tr id="gr_svn7768_684"

><td id="684"><a href="#684">684</a></td></tr
><tr id="gr_svn7768_685"

><td id="685"><a href="#685">685</a></td></tr
><tr id="gr_svn7768_686"

><td id="686"><a href="#686">686</a></td></tr
><tr id="gr_svn7768_687"

><td id="687"><a href="#687">687</a></td></tr
><tr id="gr_svn7768_688"

><td id="688"><a href="#688">688</a></td></tr
><tr id="gr_svn7768_689"

><td id="689"><a href="#689">689</a></td></tr
><tr id="gr_svn7768_690"

><td id="690"><a href="#690">690</a></td></tr
><tr id="gr_svn7768_691"

><td id="691"><a href="#691">691</a></td></tr
><tr id="gr_svn7768_692"

><td id="692"><a href="#692">692</a></td></tr
><tr id="gr_svn7768_693"

><td id="693"><a href="#693">693</a></td></tr
><tr id="gr_svn7768_694"

><td id="694"><a href="#694">694</a></td></tr
><tr id="gr_svn7768_695"

><td id="695"><a href="#695">695</a></td></tr
><tr id="gr_svn7768_696"

><td id="696"><a href="#696">696</a></td></tr
><tr id="gr_svn7768_697"

><td id="697"><a href="#697">697</a></td></tr
><tr id="gr_svn7768_698"

><td id="698"><a href="#698">698</a></td></tr
><tr id="gr_svn7768_699"

><td id="699"><a href="#699">699</a></td></tr
><tr id="gr_svn7768_700"

><td id="700"><a href="#700">700</a></td></tr
><tr id="gr_svn7768_701"

><td id="701"><a href="#701">701</a></td></tr
><tr id="gr_svn7768_702"

><td id="702"><a href="#702">702</a></td></tr
><tr id="gr_svn7768_703"

><td id="703"><a href="#703">703</a></td></tr
><tr id="gr_svn7768_704"

><td id="704"><a href="#704">704</a></td></tr
><tr id="gr_svn7768_705"

><td id="705"><a href="#705">705</a></td></tr
><tr id="gr_svn7768_706"

><td id="706"><a href="#706">706</a></td></tr
><tr id="gr_svn7768_707"

><td id="707"><a href="#707">707</a></td></tr
><tr id="gr_svn7768_708"

><td id="708"><a href="#708">708</a></td></tr
><tr id="gr_svn7768_709"

><td id="709"><a href="#709">709</a></td></tr
><tr id="gr_svn7768_710"

><td id="710"><a href="#710">710</a></td></tr
><tr id="gr_svn7768_711"

><td id="711"><a href="#711">711</a></td></tr
><tr id="gr_svn7768_712"

><td id="712"><a href="#712">712</a></td></tr
><tr id="gr_svn7768_713"

><td id="713"><a href="#713">713</a></td></tr
><tr id="gr_svn7768_714"

><td id="714"><a href="#714">714</a></td></tr
><tr id="gr_svn7768_715"

><td id="715"><a href="#715">715</a></td></tr
><tr id="gr_svn7768_716"

><td id="716"><a href="#716">716</a></td></tr
><tr id="gr_svn7768_717"

><td id="717"><a href="#717">717</a></td></tr
><tr id="gr_svn7768_718"

><td id="718"><a href="#718">718</a></td></tr
><tr id="gr_svn7768_719"

><td id="719"><a href="#719">719</a></td></tr
><tr id="gr_svn7768_720"

><td id="720"><a href="#720">720</a></td></tr
><tr id="gr_svn7768_721"

><td id="721"><a href="#721">721</a></td></tr
><tr id="gr_svn7768_722"

><td id="722"><a href="#722">722</a></td></tr
><tr id="gr_svn7768_723"

><td id="723"><a href="#723">723</a></td></tr
><tr id="gr_svn7768_724"

><td id="724"><a href="#724">724</a></td></tr
><tr id="gr_svn7768_725"

><td id="725"><a href="#725">725</a></td></tr
><tr id="gr_svn7768_726"

><td id="726"><a href="#726">726</a></td></tr
><tr id="gr_svn7768_727"

><td id="727"><a href="#727">727</a></td></tr
><tr id="gr_svn7768_728"

><td id="728"><a href="#728">728</a></td></tr
><tr id="gr_svn7768_729"

><td id="729"><a href="#729">729</a></td></tr
><tr id="gr_svn7768_730"

><td id="730"><a href="#730">730</a></td></tr
><tr id="gr_svn7768_731"

><td id="731"><a href="#731">731</a></td></tr
><tr id="gr_svn7768_732"

><td id="732"><a href="#732">732</a></td></tr
><tr id="gr_svn7768_733"

><td id="733"><a href="#733">733</a></td></tr
><tr id="gr_svn7768_734"

><td id="734"><a href="#734">734</a></td></tr
><tr id="gr_svn7768_735"

><td id="735"><a href="#735">735</a></td></tr
><tr id="gr_svn7768_736"

><td id="736"><a href="#736">736</a></td></tr
><tr id="gr_svn7768_737"

><td id="737"><a href="#737">737</a></td></tr
><tr id="gr_svn7768_738"

><td id="738"><a href="#738">738</a></td></tr
><tr id="gr_svn7768_739"

><td id="739"><a href="#739">739</a></td></tr
><tr id="gr_svn7768_740"

><td id="740"><a href="#740">740</a></td></tr
><tr id="gr_svn7768_741"

><td id="741"><a href="#741">741</a></td></tr
><tr id="gr_svn7768_742"

><td id="742"><a href="#742">742</a></td></tr
><tr id="gr_svn7768_743"

><td id="743"><a href="#743">743</a></td></tr
><tr id="gr_svn7768_744"

><td id="744"><a href="#744">744</a></td></tr
><tr id="gr_svn7768_745"

><td id="745"><a href="#745">745</a></td></tr
><tr id="gr_svn7768_746"

><td id="746"><a href="#746">746</a></td></tr
><tr id="gr_svn7768_747"

><td id="747"><a href="#747">747</a></td></tr
><tr id="gr_svn7768_748"

><td id="748"><a href="#748">748</a></td></tr
><tr id="gr_svn7768_749"

><td id="749"><a href="#749">749</a></td></tr
><tr id="gr_svn7768_750"

><td id="750"><a href="#750">750</a></td></tr
><tr id="gr_svn7768_751"

><td id="751"><a href="#751">751</a></td></tr
><tr id="gr_svn7768_752"

><td id="752"><a href="#752">752</a></td></tr
><tr id="gr_svn7768_753"

><td id="753"><a href="#753">753</a></td></tr
><tr id="gr_svn7768_754"

><td id="754"><a href="#754">754</a></td></tr
><tr id="gr_svn7768_755"

><td id="755"><a href="#755">755</a></td></tr
><tr id="gr_svn7768_756"

><td id="756"><a href="#756">756</a></td></tr
><tr id="gr_svn7768_757"

><td id="757"><a href="#757">757</a></td></tr
><tr id="gr_svn7768_758"

><td id="758"><a href="#758">758</a></td></tr
><tr id="gr_svn7768_759"

><td id="759"><a href="#759">759</a></td></tr
><tr id="gr_svn7768_760"

><td id="760"><a href="#760">760</a></td></tr
><tr id="gr_svn7768_761"

><td id="761"><a href="#761">761</a></td></tr
><tr id="gr_svn7768_762"

><td id="762"><a href="#762">762</a></td></tr
><tr id="gr_svn7768_763"

><td id="763"><a href="#763">763</a></td></tr
><tr id="gr_svn7768_764"

><td id="764"><a href="#764">764</a></td></tr
><tr id="gr_svn7768_765"

><td id="765"><a href="#765">765</a></td></tr
><tr id="gr_svn7768_766"

><td id="766"><a href="#766">766</a></td></tr
><tr id="gr_svn7768_767"

><td id="767"><a href="#767">767</a></td></tr
><tr id="gr_svn7768_768"

><td id="768"><a href="#768">768</a></td></tr
><tr id="gr_svn7768_769"

><td id="769"><a href="#769">769</a></td></tr
><tr id="gr_svn7768_770"

><td id="770"><a href="#770">770</a></td></tr
><tr id="gr_svn7768_771"

><td id="771"><a href="#771">771</a></td></tr
><tr id="gr_svn7768_772"

><td id="772"><a href="#772">772</a></td></tr
><tr id="gr_svn7768_773"

><td id="773"><a href="#773">773</a></td></tr
><tr id="gr_svn7768_774"

><td id="774"><a href="#774">774</a></td></tr
><tr id="gr_svn7768_775"

><td id="775"><a href="#775">775</a></td></tr
><tr id="gr_svn7768_776"

><td id="776"><a href="#776">776</a></td></tr
><tr id="gr_svn7768_777"

><td id="777"><a href="#777">777</a></td></tr
><tr id="gr_svn7768_778"

><td id="778"><a href="#778">778</a></td></tr
><tr id="gr_svn7768_779"

><td id="779"><a href="#779">779</a></td></tr
><tr id="gr_svn7768_780"

><td id="780"><a href="#780">780</a></td></tr
><tr id="gr_svn7768_781"

><td id="781"><a href="#781">781</a></td></tr
><tr id="gr_svn7768_782"

><td id="782"><a href="#782">782</a></td></tr
><tr id="gr_svn7768_783"

><td id="783"><a href="#783">783</a></td></tr
><tr id="gr_svn7768_784"

><td id="784"><a href="#784">784</a></td></tr
><tr id="gr_svn7768_785"

><td id="785"><a href="#785">785</a></td></tr
><tr id="gr_svn7768_786"

><td id="786"><a href="#786">786</a></td></tr
><tr id="gr_svn7768_787"

><td id="787"><a href="#787">787</a></td></tr
><tr id="gr_svn7768_788"

><td id="788"><a href="#788">788</a></td></tr
><tr id="gr_svn7768_789"

><td id="789"><a href="#789">789</a></td></tr
><tr id="gr_svn7768_790"

><td id="790"><a href="#790">790</a></td></tr
><tr id="gr_svn7768_791"

><td id="791"><a href="#791">791</a></td></tr
><tr id="gr_svn7768_792"

><td id="792"><a href="#792">792</a></td></tr
><tr id="gr_svn7768_793"

><td id="793"><a href="#793">793</a></td></tr
><tr id="gr_svn7768_794"

><td id="794"><a href="#794">794</a></td></tr
><tr id="gr_svn7768_795"

><td id="795"><a href="#795">795</a></td></tr
><tr id="gr_svn7768_796"

><td id="796"><a href="#796">796</a></td></tr
><tr id="gr_svn7768_797"

><td id="797"><a href="#797">797</a></td></tr
><tr id="gr_svn7768_798"

><td id="798"><a href="#798">798</a></td></tr
><tr id="gr_svn7768_799"

><td id="799"><a href="#799">799</a></td></tr
><tr id="gr_svn7768_800"

><td id="800"><a href="#800">800</a></td></tr
><tr id="gr_svn7768_801"

><td id="801"><a href="#801">801</a></td></tr
><tr id="gr_svn7768_802"

><td id="802"><a href="#802">802</a></td></tr
><tr id="gr_svn7768_803"

><td id="803"><a href="#803">803</a></td></tr
><tr id="gr_svn7768_804"

><td id="804"><a href="#804">804</a></td></tr
><tr id="gr_svn7768_805"

><td id="805"><a href="#805">805</a></td></tr
><tr id="gr_svn7768_806"

><td id="806"><a href="#806">806</a></td></tr
><tr id="gr_svn7768_807"

><td id="807"><a href="#807">807</a></td></tr
><tr id="gr_svn7768_808"

><td id="808"><a href="#808">808</a></td></tr
><tr id="gr_svn7768_809"

><td id="809"><a href="#809">809</a></td></tr
><tr id="gr_svn7768_810"

><td id="810"><a href="#810">810</a></td></tr
><tr id="gr_svn7768_811"

><td id="811"><a href="#811">811</a></td></tr
><tr id="gr_svn7768_812"

><td id="812"><a href="#812">812</a></td></tr
><tr id="gr_svn7768_813"

><td id="813"><a href="#813">813</a></td></tr
><tr id="gr_svn7768_814"

><td id="814"><a href="#814">814</a></td></tr
><tr id="gr_svn7768_815"

><td id="815"><a href="#815">815</a></td></tr
><tr id="gr_svn7768_816"

><td id="816"><a href="#816">816</a></td></tr
><tr id="gr_svn7768_817"

><td id="817"><a href="#817">817</a></td></tr
><tr id="gr_svn7768_818"

><td id="818"><a href="#818">818</a></td></tr
><tr id="gr_svn7768_819"

><td id="819"><a href="#819">819</a></td></tr
><tr id="gr_svn7768_820"

><td id="820"><a href="#820">820</a></td></tr
><tr id="gr_svn7768_821"

><td id="821"><a href="#821">821</a></td></tr
><tr id="gr_svn7768_822"

><td id="822"><a href="#822">822</a></td></tr
><tr id="gr_svn7768_823"

><td id="823"><a href="#823">823</a></td></tr
><tr id="gr_svn7768_824"

><td id="824"><a href="#824">824</a></td></tr
><tr id="gr_svn7768_825"

><td id="825"><a href="#825">825</a></td></tr
><tr id="gr_svn7768_826"

><td id="826"><a href="#826">826</a></td></tr
><tr id="gr_svn7768_827"

><td id="827"><a href="#827">827</a></td></tr
><tr id="gr_svn7768_828"

><td id="828"><a href="#828">828</a></td></tr
><tr id="gr_svn7768_829"

><td id="829"><a href="#829">829</a></td></tr
><tr id="gr_svn7768_830"

><td id="830"><a href="#830">830</a></td></tr
><tr id="gr_svn7768_831"

><td id="831"><a href="#831">831</a></td></tr
><tr id="gr_svn7768_832"

><td id="832"><a href="#832">832</a></td></tr
><tr id="gr_svn7768_833"

><td id="833"><a href="#833">833</a></td></tr
><tr id="gr_svn7768_834"

><td id="834"><a href="#834">834</a></td></tr
><tr id="gr_svn7768_835"

><td id="835"><a href="#835">835</a></td></tr
><tr id="gr_svn7768_836"

><td id="836"><a href="#836">836</a></td></tr
><tr id="gr_svn7768_837"

><td id="837"><a href="#837">837</a></td></tr
><tr id="gr_svn7768_838"

><td id="838"><a href="#838">838</a></td></tr
><tr id="gr_svn7768_839"

><td id="839"><a href="#839">839</a></td></tr
><tr id="gr_svn7768_840"

><td id="840"><a href="#840">840</a></td></tr
><tr id="gr_svn7768_841"

><td id="841"><a href="#841">841</a></td></tr
><tr id="gr_svn7768_842"

><td id="842"><a href="#842">842</a></td></tr
><tr id="gr_svn7768_843"

><td id="843"><a href="#843">843</a></td></tr
><tr id="gr_svn7768_844"

><td id="844"><a href="#844">844</a></td></tr
><tr id="gr_svn7768_845"

><td id="845"><a href="#845">845</a></td></tr
><tr id="gr_svn7768_846"

><td id="846"><a href="#846">846</a></td></tr
><tr id="gr_svn7768_847"

><td id="847"><a href="#847">847</a></td></tr
><tr id="gr_svn7768_848"

><td id="848"><a href="#848">848</a></td></tr
><tr id="gr_svn7768_849"

><td id="849"><a href="#849">849</a></td></tr
><tr id="gr_svn7768_850"

><td id="850"><a href="#850">850</a></td></tr
><tr id="gr_svn7768_851"

><td id="851"><a href="#851">851</a></td></tr
><tr id="gr_svn7768_852"

><td id="852"><a href="#852">852</a></td></tr
><tr id="gr_svn7768_853"

><td id="853"><a href="#853">853</a></td></tr
><tr id="gr_svn7768_854"

><td id="854"><a href="#854">854</a></td></tr
><tr id="gr_svn7768_855"

><td id="855"><a href="#855">855</a></td></tr
><tr id="gr_svn7768_856"

><td id="856"><a href="#856">856</a></td></tr
><tr id="gr_svn7768_857"

><td id="857"><a href="#857">857</a></td></tr
><tr id="gr_svn7768_858"

><td id="858"><a href="#858">858</a></td></tr
><tr id="gr_svn7768_859"

><td id="859"><a href="#859">859</a></td></tr
><tr id="gr_svn7768_860"

><td id="860"><a href="#860">860</a></td></tr
><tr id="gr_svn7768_861"

><td id="861"><a href="#861">861</a></td></tr
><tr id="gr_svn7768_862"

><td id="862"><a href="#862">862</a></td></tr
><tr id="gr_svn7768_863"

><td id="863"><a href="#863">863</a></td></tr
><tr id="gr_svn7768_864"

><td id="864"><a href="#864">864</a></td></tr
><tr id="gr_svn7768_865"

><td id="865"><a href="#865">865</a></td></tr
><tr id="gr_svn7768_866"

><td id="866"><a href="#866">866</a></td></tr
><tr id="gr_svn7768_867"

><td id="867"><a href="#867">867</a></td></tr
><tr id="gr_svn7768_868"

><td id="868"><a href="#868">868</a></td></tr
><tr id="gr_svn7768_869"

><td id="869"><a href="#869">869</a></td></tr
><tr id="gr_svn7768_870"

><td id="870"><a href="#870">870</a></td></tr
><tr id="gr_svn7768_871"

><td id="871"><a href="#871">871</a></td></tr
><tr id="gr_svn7768_872"

><td id="872"><a href="#872">872</a></td></tr
><tr id="gr_svn7768_873"

><td id="873"><a href="#873">873</a></td></tr
><tr id="gr_svn7768_874"

><td id="874"><a href="#874">874</a></td></tr
><tr id="gr_svn7768_875"

><td id="875"><a href="#875">875</a></td></tr
><tr id="gr_svn7768_876"

><td id="876"><a href="#876">876</a></td></tr
><tr id="gr_svn7768_877"

><td id="877"><a href="#877">877</a></td></tr
><tr id="gr_svn7768_878"

><td id="878"><a href="#878">878</a></td></tr
><tr id="gr_svn7768_879"

><td id="879"><a href="#879">879</a></td></tr
><tr id="gr_svn7768_880"

><td id="880"><a href="#880">880</a></td></tr
><tr id="gr_svn7768_881"

><td id="881"><a href="#881">881</a></td></tr
><tr id="gr_svn7768_882"

><td id="882"><a href="#882">882</a></td></tr
><tr id="gr_svn7768_883"

><td id="883"><a href="#883">883</a></td></tr
><tr id="gr_svn7768_884"

><td id="884"><a href="#884">884</a></td></tr
><tr id="gr_svn7768_885"

><td id="885"><a href="#885">885</a></td></tr
><tr id="gr_svn7768_886"

><td id="886"><a href="#886">886</a></td></tr
><tr id="gr_svn7768_887"

><td id="887"><a href="#887">887</a></td></tr
><tr id="gr_svn7768_888"

><td id="888"><a href="#888">888</a></td></tr
><tr id="gr_svn7768_889"

><td id="889"><a href="#889">889</a></td></tr
><tr id="gr_svn7768_890"

><td id="890"><a href="#890">890</a></td></tr
><tr id="gr_svn7768_891"

><td id="891"><a href="#891">891</a></td></tr
><tr id="gr_svn7768_892"

><td id="892"><a href="#892">892</a></td></tr
><tr id="gr_svn7768_893"

><td id="893"><a href="#893">893</a></td></tr
><tr id="gr_svn7768_894"

><td id="894"><a href="#894">894</a></td></tr
><tr id="gr_svn7768_895"

><td id="895"><a href="#895">895</a></td></tr
><tr id="gr_svn7768_896"

><td id="896"><a href="#896">896</a></td></tr
><tr id="gr_svn7768_897"

><td id="897"><a href="#897">897</a></td></tr
><tr id="gr_svn7768_898"

><td id="898"><a href="#898">898</a></td></tr
><tr id="gr_svn7768_899"

><td id="899"><a href="#899">899</a></td></tr
><tr id="gr_svn7768_900"

><td id="900"><a href="#900">900</a></td></tr
><tr id="gr_svn7768_901"

><td id="901"><a href="#901">901</a></td></tr
><tr id="gr_svn7768_902"

><td id="902"><a href="#902">902</a></td></tr
><tr id="gr_svn7768_903"

><td id="903"><a href="#903">903</a></td></tr
><tr id="gr_svn7768_904"

><td id="904"><a href="#904">904</a></td></tr
><tr id="gr_svn7768_905"

><td id="905"><a href="#905">905</a></td></tr
><tr id="gr_svn7768_906"

><td id="906"><a href="#906">906</a></td></tr
><tr id="gr_svn7768_907"

><td id="907"><a href="#907">907</a></td></tr
><tr id="gr_svn7768_908"

><td id="908"><a href="#908">908</a></td></tr
><tr id="gr_svn7768_909"

><td id="909"><a href="#909">909</a></td></tr
><tr id="gr_svn7768_910"

><td id="910"><a href="#910">910</a></td></tr
><tr id="gr_svn7768_911"

><td id="911"><a href="#911">911</a></td></tr
><tr id="gr_svn7768_912"

><td id="912"><a href="#912">912</a></td></tr
><tr id="gr_svn7768_913"

><td id="913"><a href="#913">913</a></td></tr
><tr id="gr_svn7768_914"

><td id="914"><a href="#914">914</a></td></tr
><tr id="gr_svn7768_915"

><td id="915"><a href="#915">915</a></td></tr
><tr id="gr_svn7768_916"

><td id="916"><a href="#916">916</a></td></tr
><tr id="gr_svn7768_917"

><td id="917"><a href="#917">917</a></td></tr
><tr id="gr_svn7768_918"

><td id="918"><a href="#918">918</a></td></tr
><tr id="gr_svn7768_919"

><td id="919"><a href="#919">919</a></td></tr
><tr id="gr_svn7768_920"

><td id="920"><a href="#920">920</a></td></tr
><tr id="gr_svn7768_921"

><td id="921"><a href="#921">921</a></td></tr
><tr id="gr_svn7768_922"

><td id="922"><a href="#922">922</a></td></tr
><tr id="gr_svn7768_923"

><td id="923"><a href="#923">923</a></td></tr
><tr id="gr_svn7768_924"

><td id="924"><a href="#924">924</a></td></tr
><tr id="gr_svn7768_925"

><td id="925"><a href="#925">925</a></td></tr
><tr id="gr_svn7768_926"

><td id="926"><a href="#926">926</a></td></tr
><tr id="gr_svn7768_927"

><td id="927"><a href="#927">927</a></td></tr
><tr id="gr_svn7768_928"

><td id="928"><a href="#928">928</a></td></tr
><tr id="gr_svn7768_929"

><td id="929"><a href="#929">929</a></td></tr
><tr id="gr_svn7768_930"

><td id="930"><a href="#930">930</a></td></tr
><tr id="gr_svn7768_931"

><td id="931"><a href="#931">931</a></td></tr
><tr id="gr_svn7768_932"

><td id="932"><a href="#932">932</a></td></tr
><tr id="gr_svn7768_933"

><td id="933"><a href="#933">933</a></td></tr
><tr id="gr_svn7768_934"

><td id="934"><a href="#934">934</a></td></tr
><tr id="gr_svn7768_935"

><td id="935"><a href="#935">935</a></td></tr
><tr id="gr_svn7768_936"

><td id="936"><a href="#936">936</a></td></tr
><tr id="gr_svn7768_937"

><td id="937"><a href="#937">937</a></td></tr
><tr id="gr_svn7768_938"

><td id="938"><a href="#938">938</a></td></tr
><tr id="gr_svn7768_939"

><td id="939"><a href="#939">939</a></td></tr
><tr id="gr_svn7768_940"

><td id="940"><a href="#940">940</a></td></tr
><tr id="gr_svn7768_941"

><td id="941"><a href="#941">941</a></td></tr
><tr id="gr_svn7768_942"

><td id="942"><a href="#942">942</a></td></tr
><tr id="gr_svn7768_943"

><td id="943"><a href="#943">943</a></td></tr
><tr id="gr_svn7768_944"

><td id="944"><a href="#944">944</a></td></tr
><tr id="gr_svn7768_945"

><td id="945"><a href="#945">945</a></td></tr
><tr id="gr_svn7768_946"

><td id="946"><a href="#946">946</a></td></tr
><tr id="gr_svn7768_947"

><td id="947"><a href="#947">947</a></td></tr
><tr id="gr_svn7768_948"

><td id="948"><a href="#948">948</a></td></tr
><tr id="gr_svn7768_949"

><td id="949"><a href="#949">949</a></td></tr
><tr id="gr_svn7768_950"

><td id="950"><a href="#950">950</a></td></tr
><tr id="gr_svn7768_951"

><td id="951"><a href="#951">951</a></td></tr
><tr id="gr_svn7768_952"

><td id="952"><a href="#952">952</a></td></tr
><tr id="gr_svn7768_953"

><td id="953"><a href="#953">953</a></td></tr
><tr id="gr_svn7768_954"

><td id="954"><a href="#954">954</a></td></tr
><tr id="gr_svn7768_955"

><td id="955"><a href="#955">955</a></td></tr
><tr id="gr_svn7768_956"

><td id="956"><a href="#956">956</a></td></tr
><tr id="gr_svn7768_957"

><td id="957"><a href="#957">957</a></td></tr
><tr id="gr_svn7768_958"

><td id="958"><a href="#958">958</a></td></tr
><tr id="gr_svn7768_959"

><td id="959"><a href="#959">959</a></td></tr
><tr id="gr_svn7768_960"

><td id="960"><a href="#960">960</a></td></tr
><tr id="gr_svn7768_961"

><td id="961"><a href="#961">961</a></td></tr
><tr id="gr_svn7768_962"

><td id="962"><a href="#962">962</a></td></tr
><tr id="gr_svn7768_963"

><td id="963"><a href="#963">963</a></td></tr
><tr id="gr_svn7768_964"

><td id="964"><a href="#964">964</a></td></tr
><tr id="gr_svn7768_965"

><td id="965"><a href="#965">965</a></td></tr
><tr id="gr_svn7768_966"

><td id="966"><a href="#966">966</a></td></tr
><tr id="gr_svn7768_967"

><td id="967"><a href="#967">967</a></td></tr
><tr id="gr_svn7768_968"

><td id="968"><a href="#968">968</a></td></tr
><tr id="gr_svn7768_969"

><td id="969"><a href="#969">969</a></td></tr
><tr id="gr_svn7768_970"

><td id="970"><a href="#970">970</a></td></tr
><tr id="gr_svn7768_971"

><td id="971"><a href="#971">971</a></td></tr
><tr id="gr_svn7768_972"

><td id="972"><a href="#972">972</a></td></tr
><tr id="gr_svn7768_973"

><td id="973"><a href="#973">973</a></td></tr
><tr id="gr_svn7768_974"

><td id="974"><a href="#974">974</a></td></tr
><tr id="gr_svn7768_975"

><td id="975"><a href="#975">975</a></td></tr
><tr id="gr_svn7768_976"

><td id="976"><a href="#976">976</a></td></tr
><tr id="gr_svn7768_977"

><td id="977"><a href="#977">977</a></td></tr
><tr id="gr_svn7768_978"

><td id="978"><a href="#978">978</a></td></tr
><tr id="gr_svn7768_979"

><td id="979"><a href="#979">979</a></td></tr
><tr id="gr_svn7768_980"

><td id="980"><a href="#980">980</a></td></tr
><tr id="gr_svn7768_981"

><td id="981"><a href="#981">981</a></td></tr
><tr id="gr_svn7768_982"

><td id="982"><a href="#982">982</a></td></tr
><tr id="gr_svn7768_983"

><td id="983"><a href="#983">983</a></td></tr
><tr id="gr_svn7768_984"

><td id="984"><a href="#984">984</a></td></tr
><tr id="gr_svn7768_985"

><td id="985"><a href="#985">985</a></td></tr
><tr id="gr_svn7768_986"

><td id="986"><a href="#986">986</a></td></tr
><tr id="gr_svn7768_987"

><td id="987"><a href="#987">987</a></td></tr
><tr id="gr_svn7768_988"

><td id="988"><a href="#988">988</a></td></tr
><tr id="gr_svn7768_989"

><td id="989"><a href="#989">989</a></td></tr
><tr id="gr_svn7768_990"

><td id="990"><a href="#990">990</a></td></tr
><tr id="gr_svn7768_991"

><td id="991"><a href="#991">991</a></td></tr
><tr id="gr_svn7768_992"

><td id="992"><a href="#992">992</a></td></tr
><tr id="gr_svn7768_993"

><td id="993"><a href="#993">993</a></td></tr
><tr id="gr_svn7768_994"

><td id="994"><a href="#994">994</a></td></tr
><tr id="gr_svn7768_995"

><td id="995"><a href="#995">995</a></td></tr
><tr id="gr_svn7768_996"

><td id="996"><a href="#996">996</a></td></tr
><tr id="gr_svn7768_997"

><td id="997"><a href="#997">997</a></td></tr
><tr id="gr_svn7768_998"

><td id="998"><a href="#998">998</a></td></tr
><tr id="gr_svn7768_999"

><td id="999"><a href="#999">999</a></td></tr
><tr id="gr_svn7768_1000"

><td id="1000"><a href="#1000">1000</a></td></tr
><tr id="gr_svn7768_1001"

><td id="1001"><a href="#1001">1001</a></td></tr
><tr id="gr_svn7768_1002"

><td id="1002"><a href="#1002">1002</a></td></tr
><tr id="gr_svn7768_1003"

><td id="1003"><a href="#1003">1003</a></td></tr
><tr id="gr_svn7768_1004"

><td id="1004"><a href="#1004">1004</a></td></tr
><tr id="gr_svn7768_1005"

><td id="1005"><a href="#1005">1005</a></td></tr
><tr id="gr_svn7768_1006"

><td id="1006"><a href="#1006">1006</a></td></tr
><tr id="gr_svn7768_1007"

><td id="1007"><a href="#1007">1007</a></td></tr
><tr id="gr_svn7768_1008"

><td id="1008"><a href="#1008">1008</a></td></tr
><tr id="gr_svn7768_1009"

><td id="1009"><a href="#1009">1009</a></td></tr
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

><td class="source">  Copyright (c) 2004-10 Ben Fry &amp; Casey Reas<br></td></tr
><tr
id=sl_svn7768_7

><td class="source">  Copyright (c) 2001-04 Massachusetts Institute of Technology<br></td></tr
><tr
id=sl_svn7768_8

><td class="source"><br></td></tr
><tr
id=sl_svn7768_9

><td class="source">  This library is free software; you can redistribute it and/or<br></td></tr
><tr
id=sl_svn7768_10

><td class="source">  modify it under the terms of version 2.01 of the GNU Lesser General<br></td></tr
><tr
id=sl_svn7768_11

><td class="source">  Public License as published by the Free Software Foundation.<br></td></tr
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

><td class="source">import java.awt.*;<br></td></tr
><tr
id=sl_svn7768_27

><td class="source">import java.awt.image.*;<br></td></tr
><tr
id=sl_svn7768_28

><td class="source">import java.io.*;<br></td></tr
><tr
id=sl_svn7768_29

><td class="source">import java.lang.reflect.Method;<br></td></tr
><tr
id=sl_svn7768_30

><td class="source">import java.util.Arrays;<br></td></tr
><tr
id=sl_svn7768_31

><td class="source">import java.util.HashMap;<br></td></tr
><tr
id=sl_svn7768_32

><td class="source">import java.util.Set;<br></td></tr
><tr
id=sl_svn7768_33

><td class="source"><br></td></tr
><tr
id=sl_svn7768_34

><td class="source"><br></td></tr
><tr
id=sl_svn7768_35

><td class="source">/**<br></td></tr
><tr
id=sl_svn7768_36

><td class="source"> * Grayscale bitmap font class used by Processing.<br></td></tr
><tr
id=sl_svn7768_37

><td class="source"> * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_38

><td class="source"> * Awful (and by that, I mean awesome) ASCII (non-)art for how this works:<br></td></tr
><tr
id=sl_svn7768_39

><td class="source"> * &lt;PRE&gt;<br></td></tr
><tr
id=sl_svn7768_40

><td class="source"> *   |<br></td></tr
><tr
id=sl_svn7768_41

><td class="source"> *   |                   height is the full used height of the image<br></td></tr
><tr
id=sl_svn7768_42

><td class="source"> *   |<br></td></tr
><tr
id=sl_svn7768_43

><td class="source"> *   |   ..XX..       }<br></td></tr
><tr
id=sl_svn7768_44

><td class="source"> *   |   ..XX..       }<br></td></tr
><tr
id=sl_svn7768_45

><td class="source"> *   |   ......       }<br></td></tr
><tr
id=sl_svn7768_46

><td class="source"> *   |   XXXX..       }  topExtent (top y is baseline - topExtent)<br></td></tr
><tr
id=sl_svn7768_47

><td class="source"> *   |   ..XX..       }<br></td></tr
><tr
id=sl_svn7768_48

><td class="source"> *   |   ..XX..       }  dotted areas are where the image data<br></td></tr
><tr
id=sl_svn7768_49

><td class="source"> *   |   ..XX..       }  is actually located for the character<br></td></tr
><tr
id=sl_svn7768_50

><td class="source"> *   +---XXXXXX----   }  (it extends to the right and down<br></td></tr
><tr
id=sl_svn7768_51

><td class="source"> *   |                   for power of two texture sizes)<br></td></tr
><tr
id=sl_svn7768_52

><td class="source"> *   ^^^^ leftExtent (amount to move over before drawing the image<br></td></tr
><tr
id=sl_svn7768_53

><td class="source"> *<br></td></tr
><tr
id=sl_svn7768_54

><td class="source"> *   ^^^^^^^^^^^^^^ setWidth (width displaced by char)<br></td></tr
><tr
id=sl_svn7768_55

><td class="source"> * &lt;/PRE&gt;<br></td></tr
><tr
id=sl_svn7768_56

><td class="source"> */<br></td></tr
><tr
id=sl_svn7768_57

><td class="source">public class PFont implements PConstants {<br></td></tr
><tr
id=sl_svn7768_58

><td class="source"><br></td></tr
><tr
id=sl_svn7768_59

><td class="source">  /** Number of character glyphs in this font. */<br></td></tr
><tr
id=sl_svn7768_60

><td class="source">  protected int glyphCount;<br></td></tr
><tr
id=sl_svn7768_61

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_62

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_63

><td class="source">   * Actual glyph data. The length of this array won&#39;t necessarily be the <br></td></tr
><tr
id=sl_svn7768_64

><td class="source">   * same size as glyphCount, in cases where lazy font loading is in use.<br></td></tr
><tr
id=sl_svn7768_65

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_66

><td class="source">  protected Glyph[] glyphs;<br></td></tr
><tr
id=sl_svn7768_67

><td class="source"><br></td></tr
><tr
id=sl_svn7768_68

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_69

><td class="source">   * Name of the font as seen by Java when it was created.<br></td></tr
><tr
id=sl_svn7768_70

><td class="source">   * If the font is available, the native version will be used.<br></td></tr
><tr
id=sl_svn7768_71

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_72

><td class="source">  protected String name;<br></td></tr
><tr
id=sl_svn7768_73

><td class="source"><br></td></tr
><tr
id=sl_svn7768_74

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_75

><td class="source">   * Postscript name of the font that this bitmap was created from.<br></td></tr
><tr
id=sl_svn7768_76

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_77

><td class="source">  protected String psname;<br></td></tr
><tr
id=sl_svn7768_78

><td class="source"><br></td></tr
><tr
id=sl_svn7768_79

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_80

><td class="source">   * The original size of the font when it was first created <br></td></tr
><tr
id=sl_svn7768_81

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_82

><td class="source">  protected int size;<br></td></tr
><tr
id=sl_svn7768_83

><td class="source"><br></td></tr
><tr
id=sl_svn7768_84

><td class="source">  /** true if smoothing was enabled for this font, used for native impl */<br></td></tr
><tr
id=sl_svn7768_85

><td class="source">  protected boolean smooth;<br></td></tr
><tr
id=sl_svn7768_86

><td class="source"><br></td></tr
><tr
id=sl_svn7768_87

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_88

><td class="source">   * The ascent of the font. If the &#39;d&#39; character is present in this PFont, <br></td></tr
><tr
id=sl_svn7768_89

><td class="source">   * this value is replaced with its pixel height, because the values returned<br></td></tr
><tr
id=sl_svn7768_90

><td class="source">   * by FontMetrics.getAscent() seem to be terrible. <br></td></tr
><tr
id=sl_svn7768_91

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_92

><td class="source">  protected int ascent;<br></td></tr
><tr
id=sl_svn7768_93

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_94

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_95

><td class="source">   * The descent of the font. If the &#39;p&#39; character is present in this PFont, <br></td></tr
><tr
id=sl_svn7768_96

><td class="source">   * this value is replaced with its lowest pixel height, because the values <br></td></tr
><tr
id=sl_svn7768_97

><td class="source">   * returned by FontMetrics.getDescent() are gross. <br></td></tr
><tr
id=sl_svn7768_98

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_99

><td class="source">  protected int descent;<br></td></tr
><tr
id=sl_svn7768_100

><td class="source"><br></td></tr
><tr
id=sl_svn7768_101

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_102

><td class="source">   * A more efficient array lookup for straight ASCII characters. For Unicode<br></td></tr
><tr
id=sl_svn7768_103

><td class="source">   * characters, a QuickSort-style search is used. <br></td></tr
><tr
id=sl_svn7768_104

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_105

><td class="source">  protected int[] ascii;<br></td></tr
><tr
id=sl_svn7768_106

><td class="source"><br></td></tr
><tr
id=sl_svn7768_107

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_108

><td class="source">   * True if this font is set to load dynamically. This is the default when <br></td></tr
><tr
id=sl_svn7768_109

><td class="source">   * createFont() method is called without a character set. Bitmap versions of <br></td></tr
><tr
id=sl_svn7768_110

><td class="source">   * characters are only created when prompted by an index() call.<br></td></tr
><tr
id=sl_svn7768_111

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_112

><td class="source">  protected boolean lazy;<br></td></tr
><tr
id=sl_svn7768_113

><td class="source"><br></td></tr
><tr
id=sl_svn7768_114

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_115

><td class="source">   * Native Java version of the font. If possible, this allows the<br></td></tr
><tr
id=sl_svn7768_116

><td class="source">   * PGraphics subclass to just use Java&#39;s font rendering stuff<br></td></tr
><tr
id=sl_svn7768_117

><td class="source">   * in situations where that&#39;s faster.<br></td></tr
><tr
id=sl_svn7768_118

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_119

><td class="source">  protected Font font;<br></td></tr
><tr
id=sl_svn7768_120

><td class="source"><br></td></tr
><tr
id=sl_svn7768_121

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_122

><td class="source">   * True if this font was loaded from a stream, rather than from the OS.<br></td></tr
><tr
id=sl_svn7768_123

><td class="source">   * It&#39;s always safe to use the native version of a font loaded from a TTF<br></td></tr
><tr
id=sl_svn7768_124

><td class="source">   * file, since that&#39;s how it&#39;ll look when exported. Otherwise, you&#39;ll have<br></td></tr
><tr
id=sl_svn7768_125

><td class="source">   * to use hint(ENABLE_NATIVE_FONTS) to get the native version working with<br></td></tr
><tr
id=sl_svn7768_126

><td class="source">   * renderers that support it.<br></td></tr
><tr
id=sl_svn7768_127

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_128

><td class="source">  protected boolean stream;<br></td></tr
><tr
id=sl_svn7768_129

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_130

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_131

><td class="source">   * True if this font should return &#39;null&#39; for getFont(), so that the native<br></td></tr
><tr
id=sl_svn7768_132

><td class="source">   * font will be used to create a subset, but the native version of the font<br></td></tr
><tr
id=sl_svn7768_133

><td class="source">   * will not be used. <br></td></tr
><tr
id=sl_svn7768_134

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_135

><td class="source">  protected boolean subsetting; <br></td></tr
><tr
id=sl_svn7768_136

><td class="source"><br></td></tr
><tr
id=sl_svn7768_137

><td class="source">  /** True if already tried to find the native AWT version of this font. */<br></td></tr
><tr
id=sl_svn7768_138

><td class="source">  protected boolean fontSearched;<br></td></tr
><tr
id=sl_svn7768_139

><td class="source"><br></td></tr
><tr
id=sl_svn7768_140

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_141

><td class="source">   * Array of the native system fonts. Used to lookup native fonts by their <br></td></tr
><tr
id=sl_svn7768_142

><td class="source">   * PostScript name. This is a workaround for a several year old Apple Java<br></td></tr
><tr
id=sl_svn7768_143

><td class="source">   * bug that they can&#39;t be bothered to fix. <br></td></tr
><tr
id=sl_svn7768_144

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_145

><td class="source">  static protected Font[] fonts;<br></td></tr
><tr
id=sl_svn7768_146

><td class="source">  static protected HashMap&lt;String,Font&gt; fontDifferent;<br></td></tr
><tr
id=sl_svn7768_147

><td class="source"><br></td></tr
><tr
id=sl_svn7768_148

><td class="source">//  /**<br></td></tr
><tr
id=sl_svn7768_149

><td class="source">//   * If not null, this font is set to load dynamically. This is the default  <br></td></tr
><tr
id=sl_svn7768_150

><td class="source">//   * when createFont() method is called without a character set. Bitmap <br></td></tr
><tr
id=sl_svn7768_151

><td class="source">//   * versions of characters are only created when prompted by an index() call.<br></td></tr
><tr
id=sl_svn7768_152

><td class="source">//   */<br></td></tr
><tr
id=sl_svn7768_153

><td class="source">//  protected Font lazyFont;  <br></td></tr
><tr
id=sl_svn7768_154

><td class="source">  protected BufferedImage lazyImage;<br></td></tr
><tr
id=sl_svn7768_155

><td class="source">  protected Graphics2D lazyGraphics;<br></td></tr
><tr
id=sl_svn7768_156

><td class="source">  protected FontMetrics lazyMetrics;<br></td></tr
><tr
id=sl_svn7768_157

><td class="source">  protected int[] lazySamples;  <br></td></tr
><tr
id=sl_svn7768_158

><td class="source"><br></td></tr
><tr
id=sl_svn7768_159

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_160

><td class="source">  /** for subclasses that need to store metadata about the font */<br></td></tr
><tr
id=sl_svn7768_161

><td class="source">  protected HashMap&lt;PGraphics, Object&gt; cacheMap;  <br></td></tr
><tr
id=sl_svn7768_162

><td class="source"><br></td></tr
><tr
id=sl_svn7768_163

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_164

><td class="source">  public PFont() { }  // for subclasses<br></td></tr
><tr
id=sl_svn7768_165

><td class="source"><br></td></tr
><tr
id=sl_svn7768_166

><td class="source"><br></td></tr
><tr
id=sl_svn7768_167

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_168

><td class="source">   * Create a new Processing font from a native font, but don&#39;t create all the<br></td></tr
><tr
id=sl_svn7768_169

><td class="source">   * characters at once, instead wait until they&#39;re used to include them.<br></td></tr
><tr
id=sl_svn7768_170

><td class="source">   * @param font<br></td></tr
><tr
id=sl_svn7768_171

><td class="source">   * @param smooth<br></td></tr
><tr
id=sl_svn7768_172

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_173

><td class="source">  public PFont(Font font, boolean smooth) {<br></td></tr
><tr
id=sl_svn7768_174

><td class="source">    this(font, smooth, null);<br></td></tr
><tr
id=sl_svn7768_175

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_176

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_177

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_178

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_179

><td class="source">   * Create a new image-based font on the fly. If charset is set to null, <br></td></tr
><tr
id=sl_svn7768_180

><td class="source">   * the characters will only be created as bitmaps when they&#39;re drawn.<br></td></tr
><tr
id=sl_svn7768_181

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_182

><td class="source">   * @param font the font object to create from<br></td></tr
><tr
id=sl_svn7768_183

><td class="source">   * @param charset array of all unicode chars that should be included<br></td></tr
><tr
id=sl_svn7768_184

><td class="source">   * @param smooth true to enable smoothing/anti-aliasing<br></td></tr
><tr
id=sl_svn7768_185

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_186

><td class="source">  public PFont(Font font, boolean smooth, char charset[]) {<br></td></tr
><tr
id=sl_svn7768_187

><td class="source">    // save this so that we can use the native version<br></td></tr
><tr
id=sl_svn7768_188

><td class="source">    this.font = font;<br></td></tr
><tr
id=sl_svn7768_189

><td class="source">    this.smooth = smooth;<br></td></tr
><tr
id=sl_svn7768_190

><td class="source"><br></td></tr
><tr
id=sl_svn7768_191

><td class="source">    name = font.getName();<br></td></tr
><tr
id=sl_svn7768_192

><td class="source">    psname = font.getPSName();<br></td></tr
><tr
id=sl_svn7768_193

><td class="source">    size = font.getSize();<br></td></tr
><tr
id=sl_svn7768_194

><td class="source"><br></td></tr
><tr
id=sl_svn7768_195

><td class="source">    // no, i&#39;m not interested in getting off the couch<br></td></tr
><tr
id=sl_svn7768_196

><td class="source">    //lazy = true;<br></td></tr
><tr
id=sl_svn7768_197

><td class="source">    // not sure what else to do here<br></td></tr
><tr
id=sl_svn7768_198

><td class="source">    //mbox2 = 0; <br></td></tr
><tr
id=sl_svn7768_199

><td class="source"><br></td></tr
><tr
id=sl_svn7768_200

><td class="source">    int initialCount = 10;<br></td></tr
><tr
id=sl_svn7768_201

><td class="source">    glyphs = new Glyph[initialCount];<br></td></tr
><tr
id=sl_svn7768_202

><td class="source"><br></td></tr
><tr
id=sl_svn7768_203

><td class="source">    ascii = new int[128];<br></td></tr
><tr
id=sl_svn7768_204

><td class="source">    Arrays.fill(ascii, -1);<br></td></tr
><tr
id=sl_svn7768_205

><td class="source"><br></td></tr
><tr
id=sl_svn7768_206

><td class="source">    int mbox3 = size * 3;<br></td></tr
><tr
id=sl_svn7768_207

><td class="source"><br></td></tr
><tr
id=sl_svn7768_208

><td class="source">    lazyImage = new BufferedImage(mbox3, mbox3, BufferedImage.TYPE_INT_RGB);<br></td></tr
><tr
id=sl_svn7768_209

><td class="source">    lazyGraphics = (Graphics2D) lazyImage.getGraphics();<br></td></tr
><tr
id=sl_svn7768_210

><td class="source">    lazyGraphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING,<br></td></tr
><tr
id=sl_svn7768_211

><td class="source">                                  smooth ?<br></td></tr
><tr
id=sl_svn7768_212

><td class="source">                                  RenderingHints.VALUE_ANTIALIAS_ON :<br></td></tr
><tr
id=sl_svn7768_213

><td class="source">                                  RenderingHints.VALUE_ANTIALIAS_OFF);<br></td></tr
><tr
id=sl_svn7768_214

><td class="source">    // adding this for post-1.0.9<br></td></tr
><tr
id=sl_svn7768_215

><td class="source">    lazyGraphics.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,<br></td></tr
><tr
id=sl_svn7768_216

><td class="source">                                  smooth ?<br></td></tr
><tr
id=sl_svn7768_217

><td class="source">                                  RenderingHints.VALUE_TEXT_ANTIALIAS_ON :<br></td></tr
><tr
id=sl_svn7768_218

><td class="source">                                  RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);<br></td></tr
><tr
id=sl_svn7768_219

><td class="source"><br></td></tr
><tr
id=sl_svn7768_220

><td class="source">    lazyGraphics.setFont(font);<br></td></tr
><tr
id=sl_svn7768_221

><td class="source">    lazyMetrics = lazyGraphics.getFontMetrics();<br></td></tr
><tr
id=sl_svn7768_222

><td class="source">    lazySamples = new int[mbox3 * mbox3];<br></td></tr
><tr
id=sl_svn7768_223

><td class="source"><br></td></tr
><tr
id=sl_svn7768_224

><td class="source">    // These values are terrible/unusable. Verified again for Processing 1.1.<br></td></tr
><tr
id=sl_svn7768_225

><td class="source">    // They vary widely per-platform and per-font, so instead we&#39;ll use the <br></td></tr
><tr
id=sl_svn7768_226

><td class="source">    // calculate-by-hand method of measuring pixels in characters.<br></td></tr
><tr
id=sl_svn7768_227

><td class="source">    //ascent = lazyMetrics.getAscent();<br></td></tr
><tr
id=sl_svn7768_228

><td class="source">    //descent = lazyMetrics.getDescent();<br></td></tr
><tr
id=sl_svn7768_229

><td class="source"><br></td></tr
><tr
id=sl_svn7768_230

><td class="source">    if (charset == null) {<br></td></tr
><tr
id=sl_svn7768_231

><td class="source">      lazy = true;<br></td></tr
><tr
id=sl_svn7768_232

><td class="source">//      lazyFont = font;<br></td></tr
><tr
id=sl_svn7768_233

><td class="source"><br></td></tr
><tr
id=sl_svn7768_234

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_235

><td class="source">      // charset needs to be sorted to make index lookup run more quickly<br></td></tr
><tr
id=sl_svn7768_236

><td class="source">      // http://dev.processing.org/bugs/show_bug.cgi?id=494<br></td></tr
><tr
id=sl_svn7768_237

><td class="source">      Arrays.sort(charset);<br></td></tr
><tr
id=sl_svn7768_238

><td class="source"><br></td></tr
><tr
id=sl_svn7768_239

><td class="source">      glyphs = new Glyph[charset.length];<br></td></tr
><tr
id=sl_svn7768_240

><td class="source"><br></td></tr
><tr
id=sl_svn7768_241

><td class="source">      glyphCount = 0;<br></td></tr
><tr
id=sl_svn7768_242

><td class="source">      for (char c : charset) {<br></td></tr
><tr
id=sl_svn7768_243

><td class="source">        if (font.canDisplay(c)) {<br></td></tr
><tr
id=sl_svn7768_244

><td class="source">          Glyph glyf = new Glyph(c);<br></td></tr
><tr
id=sl_svn7768_245

><td class="source">          if (glyf.value &lt; 128) {<br></td></tr
><tr
id=sl_svn7768_246

><td class="source">            ascii[glyf.value] = glyphCount;<br></td></tr
><tr
id=sl_svn7768_247

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_248

><td class="source">          glyf.index = glyphCount;<br></td></tr
><tr
id=sl_svn7768_249

><td class="source">          glyphs[glyphCount++] = glyf;           <br></td></tr
><tr
id=sl_svn7768_250

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_251

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_252

><td class="source"><br></td></tr
><tr
id=sl_svn7768_253

><td class="source">      // shorten the array if necessary<br></td></tr
><tr
id=sl_svn7768_254

><td class="source">      if (glyphCount != charset.length) {<br></td></tr
><tr
id=sl_svn7768_255

><td class="source">        glyphs = (Glyph[]) PApplet.subset(glyphs, 0, glyphCount);<br></td></tr
><tr
id=sl_svn7768_256

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_257

><td class="source"><br></td></tr
><tr
id=sl_svn7768_258

><td class="source">      // foreign font, so just make ascent the max topExtent<br></td></tr
><tr
id=sl_svn7768_259

><td class="source">      // for &gt; 1.0.9, not doing this anymore. <br></td></tr
><tr
id=sl_svn7768_260

><td class="source">      // instead using getAscent() and getDescent() values for these cases.<br></td></tr
><tr
id=sl_svn7768_261

><td class="source">//      if ((ascent == 0) &amp;&amp; (descent == 0)) {<br></td></tr
><tr
id=sl_svn7768_262

><td class="source">//        //for (int i = 0; i &lt; charCount; i++) {<br></td></tr
><tr
id=sl_svn7768_263

><td class="source">//        for (Glyph glyph : glyphs) {<br></td></tr
><tr
id=sl_svn7768_264

><td class="source">//          char cc = (char) glyph.value;<br></td></tr
><tr
id=sl_svn7768_265

><td class="source">//          //char cc = (char) glyphs[i].value;<br></td></tr
><tr
id=sl_svn7768_266

><td class="source">//          if (Character.isWhitespace(cc) ||<br></td></tr
><tr
id=sl_svn7768_267

><td class="source">//              (cc == &#39;\u00A0&#39;) || (cc == &#39;\u2007&#39;) || (cc == &#39;\u202F&#39;)) {<br></td></tr
><tr
id=sl_svn7768_268

><td class="source">//            continue;<br></td></tr
><tr
id=sl_svn7768_269

><td class="source">//          }<br></td></tr
><tr
id=sl_svn7768_270

><td class="source">//          if (glyph.topExtent &gt; ascent) {<br></td></tr
><tr
id=sl_svn7768_271

><td class="source">//            ascent = glyph.topExtent;<br></td></tr
><tr
id=sl_svn7768_272

><td class="source">//          }<br></td></tr
><tr
id=sl_svn7768_273

><td class="source">//          int d = -glyph.topExtent + glyph.height;<br></td></tr
><tr
id=sl_svn7768_274

><td class="source">//          if (d &gt; descent) {<br></td></tr
><tr
id=sl_svn7768_275

><td class="source">//            descent = d;<br></td></tr
><tr
id=sl_svn7768_276

><td class="source">//          }<br></td></tr
><tr
id=sl_svn7768_277

><td class="source">//        }<br></td></tr
><tr
id=sl_svn7768_278

><td class="source">//      }<br></td></tr
><tr
id=sl_svn7768_279

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_280

><td class="source"><br></td></tr
><tr
id=sl_svn7768_281

><td class="source">    // If not already created, just create these two characters to calculate <br></td></tr
><tr
id=sl_svn7768_282

><td class="source">    // the ascent and descent values for the font. This was tested to only <br></td></tr
><tr
id=sl_svn7768_283

><td class="source">    // require 5-10 ms on a 2.4 GHz MacBook Pro.<br></td></tr
><tr
id=sl_svn7768_284

><td class="source">    // In versions 1.0.9 and earlier, fonts that could not display d or p<br></td></tr
><tr
id=sl_svn7768_285

><td class="source">    // used the max up/down values as calculated by looking through the font.<br></td></tr
><tr
id=sl_svn7768_286

><td class="source">    // That&#39;s no longer valid with the auto-generating fonts, so we&#39;ll just<br></td></tr
><tr
id=sl_svn7768_287

><td class="source">    // use getAscent() and getDescent() in such (minor) cases.<br></td></tr
><tr
id=sl_svn7768_288

><td class="source">    if (ascent == 0) {<br></td></tr
><tr
id=sl_svn7768_289

><td class="source">      if (font.canDisplay(&#39;d&#39;)) {<br></td></tr
><tr
id=sl_svn7768_290

><td class="source">        new Glyph(&#39;d&#39;);<br></td></tr
><tr
id=sl_svn7768_291

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_292

><td class="source">        ascent = lazyMetrics.getAscent();<br></td></tr
><tr
id=sl_svn7768_293

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_294

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_295

><td class="source">    if (descent == 0) {<br></td></tr
><tr
id=sl_svn7768_296

><td class="source">      if (font.canDisplay(&#39;p&#39;)) {<br></td></tr
><tr
id=sl_svn7768_297

><td class="source">        new Glyph(&#39;p&#39;);<br></td></tr
><tr
id=sl_svn7768_298

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_299

><td class="source">        descent = lazyMetrics.getDescent();<br></td></tr
><tr
id=sl_svn7768_300

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_301

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_302

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_303

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_304

><td class="source"><br></td></tr
><tr
id=sl_svn7768_305

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_306

><td class="source">   * Adds an additional parameter that indicates the font came from a file, <br></td></tr
><tr
id=sl_svn7768_307

><td class="source">   * not a built-in OS font. <br></td></tr
><tr
id=sl_svn7768_308

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_309

><td class="source">  public PFont(Font font, boolean smooth, char charset[], boolean stream) {<br></td></tr
><tr
id=sl_svn7768_310

><td class="source">    this(font, smooth, charset);<br></td></tr
><tr
id=sl_svn7768_311

><td class="source">    this.stream = stream;<br></td></tr
><tr
id=sl_svn7768_312

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_313

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_314

><td class="source"><br></td></tr
><tr
id=sl_svn7768_315

><td class="source">  public PFont(InputStream input) throws IOException {<br></td></tr
><tr
id=sl_svn7768_316

><td class="source">    DataInputStream is = new DataInputStream(input);<br></td></tr
><tr
id=sl_svn7768_317

><td class="source"><br></td></tr
><tr
id=sl_svn7768_318

><td class="source">    // number of character images stored in this font<br></td></tr
><tr
id=sl_svn7768_319

><td class="source">    glyphCount = is.readInt();<br></td></tr
><tr
id=sl_svn7768_320

><td class="source"><br></td></tr
><tr
id=sl_svn7768_321

><td class="source">    // used to be the bitCount, but now used for version number.<br></td></tr
><tr
id=sl_svn7768_322

><td class="source">    // version 8 is any font before 69, so 9 is anything from 83+<br></td></tr
><tr
id=sl_svn7768_323

><td class="source">    // 9 was buggy so gonna increment to 10.<br></td></tr
><tr
id=sl_svn7768_324

><td class="source">    int version = is.readInt();<br></td></tr
><tr
id=sl_svn7768_325

><td class="source"><br></td></tr
><tr
id=sl_svn7768_326

><td class="source">    // this was formerly ignored, now it&#39;s the actual font size<br></td></tr
><tr
id=sl_svn7768_327

><td class="source">    //mbox = is.readInt();<br></td></tr
><tr
id=sl_svn7768_328

><td class="source">    size = is.readInt();<br></td></tr
><tr
id=sl_svn7768_329

><td class="source"><br></td></tr
><tr
id=sl_svn7768_330

><td class="source">    // this was formerly mboxY, the one that was used<br></td></tr
><tr
id=sl_svn7768_331

><td class="source">    // this will make new fonts downward compatible<br></td></tr
><tr
id=sl_svn7768_332

><td class="source">    is.readInt();  // ignore the other mbox attribute<br></td></tr
><tr
id=sl_svn7768_333

><td class="source"><br></td></tr
><tr
id=sl_svn7768_334

><td class="source">    ascent  = is.readInt();  // formerly baseHt (zero/ignored)<br></td></tr
><tr
id=sl_svn7768_335

><td class="source">    descent = is.readInt();  // formerly ignored struct padding<br></td></tr
><tr
id=sl_svn7768_336

><td class="source"><br></td></tr
><tr
id=sl_svn7768_337

><td class="source">    // allocate enough space for the character info<br></td></tr
><tr
id=sl_svn7768_338

><td class="source">    glyphs = new Glyph[glyphCount];<br></td></tr
><tr
id=sl_svn7768_339

><td class="source"><br></td></tr
><tr
id=sl_svn7768_340

><td class="source">    ascii = new int[128];<br></td></tr
><tr
id=sl_svn7768_341

><td class="source">    Arrays.fill(ascii, -1);<br></td></tr
><tr
id=sl_svn7768_342

><td class="source"><br></td></tr
><tr
id=sl_svn7768_343

><td class="source">    // read the information about the individual characters<br></td></tr
><tr
id=sl_svn7768_344

><td class="source">    for (int i = 0; i &lt; glyphCount; i++) {<br></td></tr
><tr
id=sl_svn7768_345

><td class="source">      Glyph glyph = new Glyph(is);<br></td></tr
><tr
id=sl_svn7768_346

><td class="source">      // cache locations of the ascii charset<br></td></tr
><tr
id=sl_svn7768_347

><td class="source">      if (glyph.value &lt; 128) {<br></td></tr
><tr
id=sl_svn7768_348

><td class="source">        ascii[glyph.value] = i;<br></td></tr
><tr
id=sl_svn7768_349

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_350

><td class="source">      glyph.index = i;<br></td></tr
><tr
id=sl_svn7768_351

><td class="source">      glyphs[i] = glyph;<br></td></tr
><tr
id=sl_svn7768_352

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_353

><td class="source"><br></td></tr
><tr
id=sl_svn7768_354

><td class="source">    // not a roman font, so throw an error and ask to re-build.<br></td></tr
><tr
id=sl_svn7768_355

><td class="source">    // that way can avoid a bunch of error checking hacks in here.<br></td></tr
><tr
id=sl_svn7768_356

><td class="source">    if ((ascent == 0) &amp;&amp; (descent == 0)) {<br></td></tr
><tr
id=sl_svn7768_357

><td class="source">      throw new RuntimeException(&quot;Please use \&quot;Create Font\&quot; to &quot; +<br></td></tr
><tr
id=sl_svn7768_358

><td class="source">                                 &quot;re-create this font.&quot;);<br></td></tr
><tr
id=sl_svn7768_359

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_360

><td class="source"><br></td></tr
><tr
id=sl_svn7768_361

><td class="source">    for (Glyph glyph : glyphs) {<br></td></tr
><tr
id=sl_svn7768_362

><td class="source">      glyph.readBitmap(is);<br></td></tr
><tr
id=sl_svn7768_363

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_364

><td class="source"><br></td></tr
><tr
id=sl_svn7768_365

><td class="source">    if (version &gt;= 10) {  // includes the font name at the end of the file<br></td></tr
><tr
id=sl_svn7768_366

><td class="source">      name = is.readUTF();<br></td></tr
><tr
id=sl_svn7768_367

><td class="source">      psname = is.readUTF();<br></td></tr
><tr
id=sl_svn7768_368

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_369

><td class="source">    if (version == 11) {<br></td></tr
><tr
id=sl_svn7768_370

><td class="source">      smooth = is.readBoolean();<br></td></tr
><tr
id=sl_svn7768_371

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_372

><td class="source">    // See if there&#39;s a native version of this font that can be used, <br></td></tr
><tr
id=sl_svn7768_373

><td class="source">    // in case that&#39;s of interest later.<br></td></tr
><tr
id=sl_svn7768_374

><td class="source">    findFont();<br></td></tr
><tr
id=sl_svn7768_375

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_376

><td class="source"><br></td></tr
><tr
id=sl_svn7768_377

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_378

><td class="source">  void delete() {<br></td></tr
><tr
id=sl_svn7768_379

><td class="source">    if (cacheMap != null) {    <br></td></tr
><tr
id=sl_svn7768_380

><td class="source">      Set&lt;PGraphics&gt; keySet = cacheMap.keySet();<br></td></tr
><tr
id=sl_svn7768_381

><td class="source">      if (!keySet.isEmpty()) {<br></td></tr
><tr
id=sl_svn7768_382

><td class="source">        Object[] keys = keySet.toArray();<br></td></tr
><tr
id=sl_svn7768_383

><td class="source">        for (int i = 0; i &lt; keys.length; i++) {<br></td></tr
><tr
id=sl_svn7768_384

><td class="source">          Object data = getCache((PGraphics)keys[i]);<br></td></tr
><tr
id=sl_svn7768_385

><td class="source">          Method del = null;<br></td></tr
><tr
id=sl_svn7768_386

><td class="source">          <br></td></tr
><tr
id=sl_svn7768_387

><td class="source">          try {<br></td></tr
><tr
id=sl_svn7768_388

><td class="source">            Class&lt;?&gt; c = data.getClass();<br></td></tr
><tr
id=sl_svn7768_389

><td class="source">            del = c.getMethod(&quot;delete&quot;, new Class[] {});<br></td></tr
><tr
id=sl_svn7768_390

><td class="source">          } catch (Exception e) {}<br></td></tr
><tr
id=sl_svn7768_391

><td class="source">          <br></td></tr
><tr
id=sl_svn7768_392

><td class="source">          if (del != null) {<br></td></tr
><tr
id=sl_svn7768_393

><td class="source">            // The metadata have a delete method. We try running it.<br></td></tr
><tr
id=sl_svn7768_394

><td class="source">            try {<br></td></tr
><tr
id=sl_svn7768_395

><td class="source">              del.invoke(data, new Object[] {});<br></td></tr
><tr
id=sl_svn7768_396

><td class="source">            } catch (Exception e) {}<br></td></tr
><tr
id=sl_svn7768_397

><td class="source">          }   <br></td></tr
><tr
id=sl_svn7768_398

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_399

><td class="source">      }    <br></td></tr
><tr
id=sl_svn7768_400

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_401

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_402

><td class="source"><br></td></tr
><tr
id=sl_svn7768_403

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_404

><td class="source">   * Write this PFont to an OutputStream.<br></td></tr
><tr
id=sl_svn7768_405

><td class="source">   * &lt;p&gt;<br></td></tr
><tr
id=sl_svn7768_406

><td class="source">   * This is used by the Create Font tool, or whatever anyone else dreams<br></td></tr
><tr
id=sl_svn7768_407

><td class="source">   * up for messing with fonts themselves.<br></td></tr
><tr
id=sl_svn7768_408

><td class="source">   * &lt;p&gt;<br></td></tr
><tr
id=sl_svn7768_409

><td class="source">   * It is assumed that the calling class will handle closing<br></td></tr
><tr
id=sl_svn7768_410

><td class="source">   * the stream when finished.<br></td></tr
><tr
id=sl_svn7768_411

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_412

><td class="source">  public void save(OutputStream output) throws IOException {<br></td></tr
><tr
id=sl_svn7768_413

><td class="source">    DataOutputStream os = new DataOutputStream(output);<br></td></tr
><tr
id=sl_svn7768_414

><td class="source"><br></td></tr
><tr
id=sl_svn7768_415

><td class="source">    os.writeInt(glyphCount);<br></td></tr
><tr
id=sl_svn7768_416

><td class="source"><br></td></tr
><tr
id=sl_svn7768_417

><td class="source">    if ((name == null) || (psname == null)) {<br></td></tr
><tr
id=sl_svn7768_418

><td class="source">      name = &quot;&quot;;<br></td></tr
><tr
id=sl_svn7768_419

><td class="source">      psname = &quot;&quot;;<br></td></tr
><tr
id=sl_svn7768_420

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_421

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_422

><td class="source">    os.writeInt(11);      // formerly numBits, now used for version number<br></td></tr
><tr
id=sl_svn7768_423

><td class="source">    os.writeInt(size);    // formerly mboxX (was 64, now 48)<br></td></tr
><tr
id=sl_svn7768_424

><td class="source">    os.writeInt(0);       // formerly mboxY, now ignored<br></td></tr
><tr
id=sl_svn7768_425

><td class="source">    os.writeInt(ascent);  // formerly baseHt (was ignored)<br></td></tr
><tr
id=sl_svn7768_426

><td class="source">    os.writeInt(descent); // formerly struct padding for c version<br></td></tr
><tr
id=sl_svn7768_427

><td class="source"><br></td></tr
><tr
id=sl_svn7768_428

><td class="source">    for (int i = 0; i &lt; glyphCount; i++) {<br></td></tr
><tr
id=sl_svn7768_429

><td class="source">      glyphs[i].writeHeader(os);<br></td></tr
><tr
id=sl_svn7768_430

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_431

><td class="source"><br></td></tr
><tr
id=sl_svn7768_432

><td class="source">    for (int i = 0; i &lt; glyphCount; i++) {<br></td></tr
><tr
id=sl_svn7768_433

><td class="source">      glyphs[i].writeBitmap(os);<br></td></tr
><tr
id=sl_svn7768_434

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_435

><td class="source"><br></td></tr
><tr
id=sl_svn7768_436

><td class="source">    // version 11<br></td></tr
><tr
id=sl_svn7768_437

><td class="source">    os.writeUTF(name);<br></td></tr
><tr
id=sl_svn7768_438

><td class="source">    os.writeUTF(psname);<br></td></tr
><tr
id=sl_svn7768_439

><td class="source">    os.writeBoolean(smooth);<br></td></tr
><tr
id=sl_svn7768_440

><td class="source"><br></td></tr
><tr
id=sl_svn7768_441

><td class="source">    os.flush();<br></td></tr
><tr
id=sl_svn7768_442

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_443

><td class="source"><br></td></tr
><tr
id=sl_svn7768_444

><td class="source"><br></td></tr
><tr
id=sl_svn7768_445

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_446

><td class="source">   * Create a new glyph, and add the character to the current font.<br></td></tr
><tr
id=sl_svn7768_447

><td class="source">   * @param c character to create an image for.<br></td></tr
><tr
id=sl_svn7768_448

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_449

><td class="source">  protected void addGlyph(char c) {<br></td></tr
><tr
id=sl_svn7768_450

><td class="source">    Glyph glyph = new Glyph(c);<br></td></tr
><tr
id=sl_svn7768_451

><td class="source"><br></td></tr
><tr
id=sl_svn7768_452

><td class="source">    if (glyphCount == glyphs.length) {<br></td></tr
><tr
id=sl_svn7768_453

><td class="source">      glyphs = (Glyph[]) PApplet.expand(glyphs);<br></td></tr
><tr
id=sl_svn7768_454

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_455

><td class="source">    if (glyphCount == 0) {<br></td></tr
><tr
id=sl_svn7768_456

><td class="source">      glyph.index = 0;<br></td></tr
><tr
id=sl_svn7768_457

><td class="source">      glyphs[glyphCount] = glyph;<br></td></tr
><tr
id=sl_svn7768_458

><td class="source">      if (glyph.value &lt; 128) {<br></td></tr
><tr
id=sl_svn7768_459

><td class="source">        ascii[glyph.value] = 0;<br></td></tr
><tr
id=sl_svn7768_460

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_461

><td class="source">      <br></td></tr
><tr
id=sl_svn7768_462

><td class="source">    } else if (glyphs[glyphCount-1].value &lt; glyph.value) {<br></td></tr
><tr
id=sl_svn7768_463

><td class="source">      glyphs[glyphCount] = glyph;<br></td></tr
><tr
id=sl_svn7768_464

><td class="source">      if (glyph.value &lt; 128) {<br></td></tr
><tr
id=sl_svn7768_465

><td class="source">        ascii[glyph.value] = glyphCount;<br></td></tr
><tr
id=sl_svn7768_466

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_467

><td class="source">      <br></td></tr
><tr
id=sl_svn7768_468

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_469

><td class="source">      for (int i = 0; i &lt; glyphCount; i++) {<br></td></tr
><tr
id=sl_svn7768_470

><td class="source">        if (glyphs[i].value &gt; c) {<br></td></tr
><tr
id=sl_svn7768_471

><td class="source">          for (int j = glyphCount; j &gt; i; --j) {<br></td></tr
><tr
id=sl_svn7768_472

><td class="source">            glyphs[j] = glyphs[j-1];<br></td></tr
><tr
id=sl_svn7768_473

><td class="source">            if (glyphs[j].value &lt; 128) {<br></td></tr
><tr
id=sl_svn7768_474

><td class="source">              ascii[glyphs[j].value] = j;<br></td></tr
><tr
id=sl_svn7768_475

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_476

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_477

><td class="source">          glyph.index = i;<br></td></tr
><tr
id=sl_svn7768_478

><td class="source">          glyphs[i] = glyph;<br></td></tr
><tr
id=sl_svn7768_479

><td class="source">          // cache locations of the ascii charset<br></td></tr
><tr
id=sl_svn7768_480

><td class="source">          if (c &lt; 128) ascii[c] = i;<br></td></tr
><tr
id=sl_svn7768_481

><td class="source">          break;<br></td></tr
><tr
id=sl_svn7768_482

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_483

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_484

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_485

><td class="source">    glyphCount++;<br></td></tr
><tr
id=sl_svn7768_486

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_487

><td class="source"><br></td></tr
><tr
id=sl_svn7768_488

><td class="source"><br></td></tr
><tr
id=sl_svn7768_489

><td class="source">  public String getName() {<br></td></tr
><tr
id=sl_svn7768_490

><td class="source">    return name;<br></td></tr
><tr
id=sl_svn7768_491

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_492

><td class="source"><br></td></tr
><tr
id=sl_svn7768_493

><td class="source"><br></td></tr
><tr
id=sl_svn7768_494

><td class="source">  public String getPostScriptName() {<br></td></tr
><tr
id=sl_svn7768_495

><td class="source">    return psname;<br></td></tr
><tr
id=sl_svn7768_496

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_497

><td class="source"><br></td></tr
><tr
id=sl_svn7768_498

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_499

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_500

><td class="source">   * Set the native complement of this font. Might be set internally via the<br></td></tr
><tr
id=sl_svn7768_501

><td class="source">   * findFont() function, or externally by a deriveFont() call if the font<br></td></tr
><tr
id=sl_svn7768_502

><td class="source">   * is resized by PGraphicsJava2D.<br></td></tr
><tr
id=sl_svn7768_503

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_504

><td class="source">  public void setFont(Font font) {<br></td></tr
><tr
id=sl_svn7768_505

><td class="source">    this.font = font;<br></td></tr
><tr
id=sl_svn7768_506

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_507

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_508

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_509

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_510

><td class="source">   * Return the native java.awt.Font associated with this PFont (if any).<br></td></tr
><tr
id=sl_svn7768_511

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_512

><td class="source">  public Font getFont() {<br></td></tr
><tr
id=sl_svn7768_513

><td class="source">    if (subsetting) {<br></td></tr
><tr
id=sl_svn7768_514

><td class="source">      return null;  // don&#39;t return the font for use<br></td></tr
><tr
id=sl_svn7768_515

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_516

><td class="source">    return font;<br></td></tr
><tr
id=sl_svn7768_517

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_518

><td class="source"><br></td></tr
><tr
id=sl_svn7768_519

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_520

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_521

><td class="source">   * Return size of this font.<br></td></tr
><tr
id=sl_svn7768_522

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_523

><td class="source">  public int getSize() {<br></td></tr
><tr
id=sl_svn7768_524

><td class="source">    return size;<br></td></tr
><tr
id=sl_svn7768_525

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_526

><td class="source">   <br></td></tr
><tr
id=sl_svn7768_527

><td class="source"><br></td></tr
><tr
id=sl_svn7768_528

><td class="source">  public boolean isStream() {<br></td></tr
><tr
id=sl_svn7768_529

><td class="source">    return stream;<br></td></tr
><tr
id=sl_svn7768_530

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_531

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_532

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_533

><td class="source">  public void setSubsetting() {<br></td></tr
><tr
id=sl_svn7768_534

><td class="source">    subsetting = true;<br></td></tr
><tr
id=sl_svn7768_535

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_536

><td class="source"><br></td></tr
><tr
id=sl_svn7768_537

><td class="source"><br></td></tr
><tr
id=sl_svn7768_538

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_539

><td class="source">   * Attempt to find the native version of this font.<br></td></tr
><tr
id=sl_svn7768_540

><td class="source">   * (Public so that it can be used by OpenGL or other renderers.)<br></td></tr
><tr
id=sl_svn7768_541

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_542

><td class="source">  public Font findFont() {<br></td></tr
><tr
id=sl_svn7768_543

><td class="source">    if (font == null) {<br></td></tr
><tr
id=sl_svn7768_544

><td class="source">      if (!fontSearched) {<br></td></tr
><tr
id=sl_svn7768_545

><td class="source">        // this font may or may not be installed<br></td></tr
><tr
id=sl_svn7768_546

><td class="source">        font = new Font(name, Font.PLAIN, size);<br></td></tr
><tr
id=sl_svn7768_547

><td class="source">        // if the ps name matches, then we&#39;re in fine shape<br></td></tr
><tr
id=sl_svn7768_548

><td class="source">        if (!font.getPSName().equals(psname)) {<br></td></tr
><tr
id=sl_svn7768_549

><td class="source">          // on osx java 1.4 (not 1.3.. ugh), you can specify the ps name<br></td></tr
><tr
id=sl_svn7768_550

><td class="source">          // of the font, so try that in case this .vlw font was created on pc<br></td></tr
><tr
id=sl_svn7768_551

><td class="source">          // and the name is different, but the ps name is found on the<br></td></tr
><tr
id=sl_svn7768_552

><td class="source">          // java 1.4 mac that&#39;s currently running this sketch.<br></td></tr
><tr
id=sl_svn7768_553

><td class="source">          font = new Font(psname, Font.PLAIN, size);<br></td></tr
><tr
id=sl_svn7768_554

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_555

><td class="source">        // check again, and if still bad, screw em<br></td></tr
><tr
id=sl_svn7768_556

><td class="source">        if (!font.getPSName().equals(psname)) {<br></td></tr
><tr
id=sl_svn7768_557

><td class="source">          font = null;<br></td></tr
><tr
id=sl_svn7768_558

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_559

><td class="source">        fontSearched = true;<br></td></tr
><tr
id=sl_svn7768_560

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_561

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_562

><td class="source">    return font;<br></td></tr
><tr
id=sl_svn7768_563

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_564

><td class="source"><br></td></tr
><tr
id=sl_svn7768_565

><td class="source"><br></td></tr
><tr
id=sl_svn7768_566

><td class="source">  public Glyph getGlyph(char c) {<br></td></tr
><tr
id=sl_svn7768_567

><td class="source">    int index = index(c);<br></td></tr
><tr
id=sl_svn7768_568

><td class="source">    return (index == -1) ? null : glyphs[index];<br></td></tr
><tr
id=sl_svn7768_569

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_570

><td class="source"><br></td></tr
><tr
id=sl_svn7768_571

><td class="source"><br></td></tr
><tr
id=sl_svn7768_572

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_573

><td class="source">   * Get index for the character.<br></td></tr
><tr
id=sl_svn7768_574

><td class="source">   * @return index into arrays or -1 if not found<br></td></tr
><tr
id=sl_svn7768_575

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_576

><td class="source">  protected int index(char c) {<br></td></tr
><tr
id=sl_svn7768_577

><td class="source">    if (lazy) {<br></td></tr
><tr
id=sl_svn7768_578

><td class="source">      int index = indexActual(c);<br></td></tr
><tr
id=sl_svn7768_579

><td class="source">      if (index != -1) {<br></td></tr
><tr
id=sl_svn7768_580

><td class="source">        return index;<br></td></tr
><tr
id=sl_svn7768_581

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_582

><td class="source">      if (font.canDisplay(c)) {<br></td></tr
><tr
id=sl_svn7768_583

><td class="source">        // create the glyph<br></td></tr
><tr
id=sl_svn7768_584

><td class="source">        addGlyph(c);<br></td></tr
><tr
id=sl_svn7768_585

><td class="source">        // now where did i put that?<br></td></tr
><tr
id=sl_svn7768_586

><td class="source">        return indexActual(c);<br></td></tr
><tr
id=sl_svn7768_587

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_588

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_589

><td class="source">        return -1;<br></td></tr
><tr
id=sl_svn7768_590

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_591

><td class="source"><br></td></tr
><tr
id=sl_svn7768_592

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_593

><td class="source">      return indexActual(c);<br></td></tr
><tr
id=sl_svn7768_594

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_595

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_596

><td class="source"><br></td></tr
><tr
id=sl_svn7768_597

><td class="source"><br></td></tr
><tr
id=sl_svn7768_598

><td class="source">  protected int indexActual(char c) {<br></td></tr
><tr
id=sl_svn7768_599

><td class="source">    // degenerate case, but the find function will have trouble<br></td></tr
><tr
id=sl_svn7768_600

><td class="source">    // if there are somehow zero chars in the lookup<br></td></tr
><tr
id=sl_svn7768_601

><td class="source">    //if (value.length == 0) return -1;<br></td></tr
><tr
id=sl_svn7768_602

><td class="source">    if (glyphCount == 0) return -1;<br></td></tr
><tr
id=sl_svn7768_603

><td class="source"><br></td></tr
><tr
id=sl_svn7768_604

><td class="source">    // quicker lookup for the ascii fellers<br></td></tr
><tr
id=sl_svn7768_605

><td class="source">    if (c &lt; 128) return ascii[c];<br></td></tr
><tr
id=sl_svn7768_606

><td class="source"><br></td></tr
><tr
id=sl_svn7768_607

><td class="source">    // some other unicode char, hunt it out<br></td></tr
><tr
id=sl_svn7768_608

><td class="source">    //return index_hunt(c, 0, value.length-1);<br></td></tr
><tr
id=sl_svn7768_609

><td class="source">    return indexHunt(c, 0, glyphCount-1);<br></td></tr
><tr
id=sl_svn7768_610

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_611

><td class="source"><br></td></tr
><tr
id=sl_svn7768_612

><td class="source"><br></td></tr
><tr
id=sl_svn7768_613

><td class="source">  protected int indexHunt(int c, int start, int stop) {<br></td></tr
><tr
id=sl_svn7768_614

><td class="source">    int pivot = (start + stop) / 2;<br></td></tr
><tr
id=sl_svn7768_615

><td class="source"><br></td></tr
><tr
id=sl_svn7768_616

><td class="source">    // if this is the char, then return it<br></td></tr
><tr
id=sl_svn7768_617

><td class="source">    if (c == glyphs[pivot].value) return pivot;<br></td></tr
><tr
id=sl_svn7768_618

><td class="source"><br></td></tr
><tr
id=sl_svn7768_619

><td class="source">    // char doesn&#39;t exist, otherwise would have been the pivot<br></td></tr
><tr
id=sl_svn7768_620

><td class="source">    //if (start == stop) return -1;<br></td></tr
><tr
id=sl_svn7768_621

><td class="source">    if (start &gt;= stop) return -1;<br></td></tr
><tr
id=sl_svn7768_622

><td class="source"><br></td></tr
><tr
id=sl_svn7768_623

><td class="source">    // if it&#39;s in the lower half, continue searching that<br></td></tr
><tr
id=sl_svn7768_624

><td class="source">    if (c &lt; glyphs[pivot].value) return indexHunt(c, start, pivot-1);<br></td></tr
><tr
id=sl_svn7768_625

><td class="source"><br></td></tr
><tr
id=sl_svn7768_626

><td class="source">    // if it&#39;s in the upper half, continue there<br></td></tr
><tr
id=sl_svn7768_627

><td class="source">    return indexHunt(c, pivot+1, stop);<br></td></tr
><tr
id=sl_svn7768_628

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_629

><td class="source"><br></td></tr
><tr
id=sl_svn7768_630

><td class="source"><br></td></tr
><tr
id=sl_svn7768_631

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_632

><td class="source">   * Currently un-implemented for .vlw fonts,<br></td></tr
><tr
id=sl_svn7768_633

><td class="source">   * but honored for layout in case subclasses use it.<br></td></tr
><tr
id=sl_svn7768_634

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_635

><td class="source">  public float kern(char a, char b) {<br></td></tr
><tr
id=sl_svn7768_636

><td class="source">    return 0;<br></td></tr
><tr
id=sl_svn7768_637

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_638

><td class="source"><br></td></tr
><tr
id=sl_svn7768_639

><td class="source"><br></td></tr
><tr
id=sl_svn7768_640

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_641

><td class="source">   * Returns the ascent of this font from the baseline.<br></td></tr
><tr
id=sl_svn7768_642

><td class="source">   * The value is based on a font of size 1.<br></td></tr
><tr
id=sl_svn7768_643

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_644

><td class="source">  public float ascent() {<br></td></tr
><tr
id=sl_svn7768_645

><td class="source">    return ((float) ascent / (float) size);<br></td></tr
><tr
id=sl_svn7768_646

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_647

><td class="source"><br></td></tr
><tr
id=sl_svn7768_648

><td class="source"><br></td></tr
><tr
id=sl_svn7768_649

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_650

><td class="source">   * Returns how far this font descends from the baseline.<br></td></tr
><tr
id=sl_svn7768_651

><td class="source">   * The value is based on a font size of 1.<br></td></tr
><tr
id=sl_svn7768_652

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_653

><td class="source">  public float descent() {<br></td></tr
><tr
id=sl_svn7768_654

><td class="source">    return ((float) descent / (float) size);<br></td></tr
><tr
id=sl_svn7768_655

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_656

><td class="source"><br></td></tr
><tr
id=sl_svn7768_657

><td class="source"><br></td></tr
><tr
id=sl_svn7768_658

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_659

><td class="source">   * Width of this character for a font of size 1.<br></td></tr
><tr
id=sl_svn7768_660

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_661

><td class="source">  public float width(char c) {<br></td></tr
><tr
id=sl_svn7768_662

><td class="source">    if (c == 32) return width(&#39;i&#39;);<br></td></tr
><tr
id=sl_svn7768_663

><td class="source"><br></td></tr
><tr
id=sl_svn7768_664

><td class="source">    int cc = index(c);<br></td></tr
><tr
id=sl_svn7768_665

><td class="source">    if (cc == -1) return 0;<br></td></tr
><tr
id=sl_svn7768_666

><td class="source"><br></td></tr
><tr
id=sl_svn7768_667

><td class="source">    return ((float) glyphs[cc].setWidth / (float) size);<br></td></tr
><tr
id=sl_svn7768_668

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_669

><td class="source"><br></td></tr
><tr
id=sl_svn7768_670

><td class="source"><br></td></tr
><tr
id=sl_svn7768_671

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_672

><td class="source"><br></td></tr
><tr
id=sl_svn7768_673

><td class="source">  // METADATA REQUIRED BY THE RENDERERS<br></td></tr
><tr
id=sl_svn7768_674

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_675

><td class="source"><br></td></tr
><tr
id=sl_svn7768_676

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_677

><td class="source">   * Store data of some kind for a renderer that requires extra metadata of<br></td></tr
><tr
id=sl_svn7768_678

><td class="source">   * some kind. Usually this is a renderer-specific representation of the<br></td></tr
><tr
id=sl_svn7768_679

><td class="source">   * font data, for instance a custom OpenGL texture for PGraphicsOpenGL2.<br></td></tr
><tr
id=sl_svn7768_680

><td class="source">   * @param renderer The PGraphics renderer associated to the font<br></td></tr
><tr
id=sl_svn7768_681

><td class="source">   * @param storage The metadata required by the renderer    <br></td></tr
><tr
id=sl_svn7768_682

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_683

><td class="source">  public void setCache(PGraphics renderer, Object storage) {<br></td></tr
><tr
id=sl_svn7768_684

><td class="source">    if (cacheMap == null) cacheMap = new HashMap&lt;PGraphics, Object&gt;();<br></td></tr
><tr
id=sl_svn7768_685

><td class="source">    cacheMap.put(renderer, storage);<br></td></tr
><tr
id=sl_svn7768_686

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_687

><td class="source"><br></td></tr
><tr
id=sl_svn7768_688

><td class="source"><br></td></tr
><tr
id=sl_svn7768_689

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_690

><td class="source">   * Get cache storage data for the specified renderer. Because each renderer<br></td></tr
><tr
id=sl_svn7768_691

><td class="source">   * will cache data in different formats, it&#39;s necessary to store cache data<br></td></tr
><tr
id=sl_svn7768_692

><td class="source">   * keyed by the renderer object. Otherwise, attempting to draw the same<br></td></tr
><tr
id=sl_svn7768_693

><td class="source">   * image to both a PGraphicsJava2D and a PGraphicsOpenGL2 will cause errors.<br></td></tr
><tr
id=sl_svn7768_694

><td class="source">   * @param renderer The PGraphics renderer associated to the font<br></td></tr
><tr
id=sl_svn7768_695

><td class="source">   * @return metadata stored for the specified renderer<br></td></tr
><tr
id=sl_svn7768_696

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_697

><td class="source">  public Object getCache(PGraphics renderer) {<br></td></tr
><tr
id=sl_svn7768_698

><td class="source">    if (cacheMap == null) return null;<br></td></tr
><tr
id=sl_svn7768_699

><td class="source">    return cacheMap.get(renderer);<br></td></tr
><tr
id=sl_svn7768_700

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_701

><td class="source"><br></td></tr
><tr
id=sl_svn7768_702

><td class="source"><br></td></tr
><tr
id=sl_svn7768_703

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_704

><td class="source">   * Remove information associated with this renderer from the cache, if any.<br></td></tr
><tr
id=sl_svn7768_705

><td class="source">   * @param parent The PGraphics renderer whose cache data should be removed<br></td></tr
><tr
id=sl_svn7768_706

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_707

><td class="source">  public void removeCache(PGraphics renderer) {<br></td></tr
><tr
id=sl_svn7768_708

><td class="source">    if (cacheMap != null) {<br></td></tr
><tr
id=sl_svn7768_709

><td class="source">      cacheMap.remove(renderer);<br></td></tr
><tr
id=sl_svn7768_710

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_711

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_712

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_713

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_714

><td class="source">  //////////////////////////////////////////////////////////////  <br></td></tr
><tr
id=sl_svn7768_715

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_716

><td class="source">  public int getGlyphCount()  {<br></td></tr
><tr
id=sl_svn7768_717

><td class="source">    return glyphCount;<br></td></tr
><tr
id=sl_svn7768_718

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_719

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_720

><td class="source">  public Glyph getGlyph(int i)  {<br></td></tr
><tr
id=sl_svn7768_721

><td class="source">    return glyphs[i];  <br></td></tr
><tr
id=sl_svn7768_722

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_723

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_724

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_725

><td class="source"><br></td></tr
><tr
id=sl_svn7768_726

><td class="source"><br></td></tr
><tr
id=sl_svn7768_727

><td class="source">  static final char[] EXTRA_CHARS = {<br></td></tr
><tr
id=sl_svn7768_728

><td class="source">    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,<br></td></tr
><tr
id=sl_svn7768_729

><td class="source">    0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,<br></td></tr
><tr
id=sl_svn7768_730

><td class="source">    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,<br></td></tr
><tr
id=sl_svn7768_731

><td class="source">    0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,<br></td></tr
><tr
id=sl_svn7768_732

><td class="source">    0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,<br></td></tr
><tr
id=sl_svn7768_733

><td class="source">    0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,<br></td></tr
><tr
id=sl_svn7768_734

><td class="source">    0x00B0, 0x00B1, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00BA,<br></td></tr
><tr
id=sl_svn7768_735

><td class="source">    0x00BB, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5,<br></td></tr
><tr
id=sl_svn7768_736

><td class="source">    0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD,<br></td></tr
><tr
id=sl_svn7768_737

><td class="source">    0x00CE, 0x00CF, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6,<br></td></tr
><tr
id=sl_svn7768_738

><td class="source">    0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DF,<br></td></tr
><tr
id=sl_svn7768_739

><td class="source">    0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,<br></td></tr
><tr
id=sl_svn7768_740

><td class="source">    0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,<br></td></tr
><tr
id=sl_svn7768_741

><td class="source">    0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8,<br></td></tr
><tr
id=sl_svn7768_742

><td class="source">    0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FF, 0x0102, 0x0103,<br></td></tr
><tr
id=sl_svn7768_743

><td class="source">    0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D, 0x010E, 0x010F,<br></td></tr
><tr
id=sl_svn7768_744

><td class="source">    0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B, 0x0131, 0x0139,<br></td></tr
><tr
id=sl_svn7768_745

><td class="source">    0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143, 0x0144, 0x0147,<br></td></tr
><tr
id=sl_svn7768_746

><td class="source">    0x0148, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0158,<br></td></tr
><tr
id=sl_svn7768_747

><td class="source">    0x0159, 0x015A, 0x015B, 0x015E, 0x015F, 0x0160, 0x0161, 0x0162,<br></td></tr
><tr
id=sl_svn7768_748

><td class="source">    0x0163, 0x0164, 0x0165, 0x016E, 0x016F, 0x0170, 0x0171, 0x0178,<br></td></tr
><tr
id=sl_svn7768_749

><td class="source">    0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E, 0x0192, 0x02C6,<br></td></tr
><tr
id=sl_svn7768_750

><td class="source">    0x02C7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC, 0x02DD, 0x03A9,<br></td></tr
><tr
id=sl_svn7768_751

><td class="source">    0x03C0, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A, 0x201C, 0x201D,<br></td></tr
><tr
id=sl_svn7768_752

><td class="source">    0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A,<br></td></tr
><tr
id=sl_svn7768_753

><td class="source">    0x2044, 0x20AC, 0x2122, 0x2202, 0x2206, 0x220F, 0x2211, 0x221A,<br></td></tr
><tr
id=sl_svn7768_754

><td class="source">    0x221E, 0x222B, 0x2248, 0x2260, 0x2264, 0x2265, 0x25CA, 0xF8FF,<br></td></tr
><tr
id=sl_svn7768_755

><td class="source">    0xFB01, 0xFB02<br></td></tr
><tr
id=sl_svn7768_756

><td class="source">  };<br></td></tr
><tr
id=sl_svn7768_757

><td class="source"><br></td></tr
><tr
id=sl_svn7768_758

><td class="source"><br></td></tr
><tr
id=sl_svn7768_759

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_760

><td class="source">   * The default Processing character set.<br></td></tr
><tr
id=sl_svn7768_761

><td class="source">   * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_762

><td class="source">   * This is the union of the Mac Roman and Windows ANSI (CP1250)<br></td></tr
><tr
id=sl_svn7768_763

><td class="source">   * character sets. ISO 8859-1 Latin 1 is Unicode characters 0x80 -&gt; 0xFF,<br></td></tr
><tr
id=sl_svn7768_764

><td class="source">   * and would seem a good standard, but in practice, most P5 users would<br></td></tr
><tr
id=sl_svn7768_765

><td class="source">   * rather have characters that they expect from their platform&#39;s fonts.<br></td></tr
><tr
id=sl_svn7768_766

><td class="source">   * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_767

><td class="source">   * This is more of an interim solution until a much better<br></td></tr
><tr
id=sl_svn7768_768

><td class="source">   * font solution can be determined. (i.e. create fonts on<br></td></tr
><tr
id=sl_svn7768_769

><td class="source">   * the fly from some sort of vector format).<br></td></tr
><tr
id=sl_svn7768_770

><td class="source">   * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_771

><td class="source">   * Not that I expect that to happen.<br></td></tr
><tr
id=sl_svn7768_772

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_773

><td class="source">  static public char[] CHARSET;<br></td></tr
><tr
id=sl_svn7768_774

><td class="source">  static {<br></td></tr
><tr
id=sl_svn7768_775

><td class="source">    CHARSET = new char[126-33+1 + EXTRA_CHARS.length];<br></td></tr
><tr
id=sl_svn7768_776

><td class="source">    int index = 0;<br></td></tr
><tr
id=sl_svn7768_777

><td class="source">    for (int i = 33; i &lt;= 126; i++) {<br></td></tr
><tr
id=sl_svn7768_778

><td class="source">      CHARSET[index++] = (char)i;<br></td></tr
><tr
id=sl_svn7768_779

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_780

><td class="source">    for (int i = 0; i &lt; EXTRA_CHARS.length; i++) {<br></td></tr
><tr
id=sl_svn7768_781

><td class="source">      CHARSET[index++] = EXTRA_CHARS[i];<br></td></tr
><tr
id=sl_svn7768_782

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_783

><td class="source">  };<br></td></tr
><tr
id=sl_svn7768_784

><td class="source"><br></td></tr
><tr
id=sl_svn7768_785

><td class="source"><br></td></tr
><tr
id=sl_svn7768_786

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_787

><td class="source">   * Get a list of the fonts installed on the system that can be used<br></td></tr
><tr
id=sl_svn7768_788

><td class="source">   * by Java. Not all fonts can be used in Java, in fact it&#39;s mostly<br></td></tr
><tr
id=sl_svn7768_789

><td class="source">   * only TrueType fonts. OpenType fonts with CFF data such as Adobe&#39;s<br></td></tr
><tr
id=sl_svn7768_790

><td class="source">   * OpenType fonts seem to have trouble (even though they&#39;re sort of<br></td></tr
><tr
id=sl_svn7768_791

><td class="source">   * TrueType fonts as well, or may have a .ttf extension). Regular<br></td></tr
><tr
id=sl_svn7768_792

><td class="source">   * PostScript fonts seem to work OK, however.<br></td></tr
><tr
id=sl_svn7768_793

><td class="source">   * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_794

><td class="source">   * Not recommended for use in applets, but this is implemented<br></td></tr
><tr
id=sl_svn7768_795

><td class="source">   * in PFont because the Java methods to access this information<br></td></tr
><tr
id=sl_svn7768_796

><td class="source">   * have changed between 1.1 and 1.4, and the 1.4 method is<br></td></tr
><tr
id=sl_svn7768_797

><td class="source">   * typical of the sort of undergraduate-level over-abstraction<br></td></tr
><tr
id=sl_svn7768_798

><td class="source">   * that the seems to have made its way into the Java API after 1.1.<br></td></tr
><tr
id=sl_svn7768_799

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_800

><td class="source">  static public String[] list() {<br></td></tr
><tr
id=sl_svn7768_801

><td class="source">    loadFonts();<br></td></tr
><tr
id=sl_svn7768_802

><td class="source">    String list[] = new String[fonts.length];<br></td></tr
><tr
id=sl_svn7768_803

><td class="source">    for (int i = 0; i &lt; list.length; i++) {<br></td></tr
><tr
id=sl_svn7768_804

><td class="source">      list[i] = fonts[i].getName();<br></td></tr
><tr
id=sl_svn7768_805

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_806

><td class="source">    return list;<br></td></tr
><tr
id=sl_svn7768_807

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_808

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_809

><td class="source"><br></td></tr
><tr
id=sl_svn7768_810

><td class="source">  static public void loadFonts() {<br></td></tr
><tr
id=sl_svn7768_811

><td class="source">    if (fonts == null) {<br></td></tr
><tr
id=sl_svn7768_812

><td class="source">      GraphicsEnvironment ge =<br></td></tr
><tr
id=sl_svn7768_813

><td class="source">        GraphicsEnvironment.getLocalGraphicsEnvironment();<br></td></tr
><tr
id=sl_svn7768_814

><td class="source">      fonts = ge.getAllFonts();<br></td></tr
><tr
id=sl_svn7768_815

><td class="source">      if (PApplet.platform == PConstants.MACOSX) {<br></td></tr
><tr
id=sl_svn7768_816

><td class="source">        fontDifferent = new HashMap&lt;String,Font&gt;();<br></td></tr
><tr
id=sl_svn7768_817

><td class="source">        for (Font font : fonts) {<br></td></tr
><tr
id=sl_svn7768_818

><td class="source">          // getName() returns the PostScript name on OS X 10.6 w/ Java 6.<br></td></tr
><tr
id=sl_svn7768_819

><td class="source">          fontDifferent.put(font.getName(), font);<br></td></tr
><tr
id=sl_svn7768_820

><td class="source">          //fontDifferent.put(font.getPSName(), font);<br></td></tr
><tr
id=sl_svn7768_821

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_822

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_823

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_824

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_825

><td class="source"><br></td></tr
><tr
id=sl_svn7768_826

><td class="source"><br></td></tr
><tr
id=sl_svn7768_827

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_828

><td class="source">   * Starting with Java 1.5, Apple broke the ability to specify most fonts.<br></td></tr
><tr
id=sl_svn7768_829

><td class="source">   * This bug was filed years ago as #4769141 at bugreporter.apple.com. More:<br></td></tr
><tr
id=sl_svn7768_830

><td class="source">   * &lt;a href=&quot;http://dev.processing.org/bugs/show_bug.cgi?id=407&quot;&gt;Bug 407&lt;/a&gt;.<br></td></tr
><tr
id=sl_svn7768_831

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_832

><td class="source">  static public Font findFont(String name) {<br></td></tr
><tr
id=sl_svn7768_833

><td class="source">    loadFonts();<br></td></tr
><tr
id=sl_svn7768_834

><td class="source">    if (PApplet.platform == PConstants.MACOSX) {<br></td></tr
><tr
id=sl_svn7768_835

><td class="source">      Font maybe = fontDifferent.get(name);<br></td></tr
><tr
id=sl_svn7768_836

><td class="source">      if (maybe != null) {<br></td></tr
><tr
id=sl_svn7768_837

><td class="source">        return maybe;<br></td></tr
><tr
id=sl_svn7768_838

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_839

><td class="source">//      for (int i = 0; i &lt; fonts.length; i++) {<br></td></tr
><tr
id=sl_svn7768_840

><td class="source">//        if (name.equals(fonts[i].getName())) {<br></td></tr
><tr
id=sl_svn7768_841

><td class="source">//          return fonts[i];<br></td></tr
><tr
id=sl_svn7768_842

><td class="source">//        }<br></td></tr
><tr
id=sl_svn7768_843

><td class="source">//      }<br></td></tr
><tr
id=sl_svn7768_844

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_845

><td class="source">    return new Font(name, Font.PLAIN, 1);<br></td></tr
><tr
id=sl_svn7768_846

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_847

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_848

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_849

><td class="source">  //////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn7768_850

><td class="source"><br></td></tr
><tr
id=sl_svn7768_851

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_852

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_853

><td class="source">   * A single character, and its visage.<br></td></tr
><tr
id=sl_svn7768_854

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_855

><td class="source">  public class Glyph {<br></td></tr
><tr
id=sl_svn7768_856

><td class="source">    public PImage image;<br></td></tr
><tr
id=sl_svn7768_857

><td class="source">    public int value;<br></td></tr
><tr
id=sl_svn7768_858

><td class="source">    public int height;<br></td></tr
><tr
id=sl_svn7768_859

><td class="source">    public int width;<br></td></tr
><tr
id=sl_svn7768_860

><td class="source">    public int index;<br></td></tr
><tr
id=sl_svn7768_861

><td class="source">    public int setWidth;<br></td></tr
><tr
id=sl_svn7768_862

><td class="source">    public int topExtent;<br></td></tr
><tr
id=sl_svn7768_863

><td class="source">    public int leftExtent;<br></td></tr
><tr
id=sl_svn7768_864

><td class="source"><br></td></tr
><tr
id=sl_svn7768_865

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_866

><td class="source">    protected Glyph() {<br></td></tr
><tr
id=sl_svn7768_867

><td class="source">      index = -1;<br></td></tr
><tr
id=sl_svn7768_868

><td class="source">      // used when reading from a stream or for subclasses<br></td></tr
><tr
id=sl_svn7768_869

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_870

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_871

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_872

><td class="source">    protected Glyph(DataInputStream is) throws IOException {<br></td></tr
><tr
id=sl_svn7768_873

><td class="source">      index = -1;<br></td></tr
><tr
id=sl_svn7768_874

><td class="source">      readHeader(is);<br></td></tr
><tr
id=sl_svn7768_875

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_876

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_877

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_878

><td class="source">    protected void readHeader(DataInputStream is) throws IOException {<br></td></tr
><tr
id=sl_svn7768_879

><td class="source">      value = is.readInt();<br></td></tr
><tr
id=sl_svn7768_880

><td class="source">      height = is.readInt();<br></td></tr
><tr
id=sl_svn7768_881

><td class="source">      width = is.readInt();<br></td></tr
><tr
id=sl_svn7768_882

><td class="source">      setWidth = is.readInt();<br></td></tr
><tr
id=sl_svn7768_883

><td class="source">      topExtent = is.readInt();<br></td></tr
><tr
id=sl_svn7768_884

><td class="source">      leftExtent = is.readInt();<br></td></tr
><tr
id=sl_svn7768_885

><td class="source"><br></td></tr
><tr
id=sl_svn7768_886

><td class="source">      // pointer from a struct in the c version, ignored<br></td></tr
><tr
id=sl_svn7768_887

><td class="source">      is.readInt();<br></td></tr
><tr
id=sl_svn7768_888

><td class="source">      <br></td></tr
><tr
id=sl_svn7768_889

><td class="source">      // the values for getAscent() and getDescent() from FontMetrics<br></td></tr
><tr
id=sl_svn7768_890

><td class="source">      // seem to be way too large.. perhaps they&#39;re the max?<br></td></tr
><tr
id=sl_svn7768_891

><td class="source">      // as such, use a more traditional marker for ascent/descent<br></td></tr
><tr
id=sl_svn7768_892

><td class="source">      if (value == &#39;d&#39;) {<br></td></tr
><tr
id=sl_svn7768_893

><td class="source">        if (ascent == 0) ascent = topExtent;<br></td></tr
><tr
id=sl_svn7768_894

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_895

><td class="source">      if (value == &#39;p&#39;) {<br></td></tr
><tr
id=sl_svn7768_896

><td class="source">        if (descent == 0) descent = -topExtent + height;<br></td></tr
><tr
id=sl_svn7768_897

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_898

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_899

><td class="source"><br></td></tr
><tr
id=sl_svn7768_900

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_901

><td class="source">    protected void writeHeader(DataOutputStream os) throws IOException {<br></td></tr
><tr
id=sl_svn7768_902

><td class="source">      os.writeInt(value);<br></td></tr
><tr
id=sl_svn7768_903

><td class="source">      os.writeInt(height);<br></td></tr
><tr
id=sl_svn7768_904

><td class="source">      os.writeInt(width);<br></td></tr
><tr
id=sl_svn7768_905

><td class="source">      os.writeInt(setWidth);<br></td></tr
><tr
id=sl_svn7768_906

><td class="source">      os.writeInt(topExtent);<br></td></tr
><tr
id=sl_svn7768_907

><td class="source">      os.writeInt(leftExtent);<br></td></tr
><tr
id=sl_svn7768_908

><td class="source">      os.writeInt(0); // padding<br></td></tr
><tr
id=sl_svn7768_909

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_910

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_911

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_912

><td class="source">    protected void readBitmap(DataInputStream is) throws IOException {<br></td></tr
><tr
id=sl_svn7768_913

><td class="source">      image = new PImage(width, height, ALPHA);<br></td></tr
><tr
id=sl_svn7768_914

><td class="source">      int bitmapSize = width * height;<br></td></tr
><tr
id=sl_svn7768_915

><td class="source"><br></td></tr
><tr
id=sl_svn7768_916

><td class="source">      byte[] temp = new byte[bitmapSize];<br></td></tr
><tr
id=sl_svn7768_917

><td class="source">      is.readFully(temp);<br></td></tr
><tr
id=sl_svn7768_918

><td class="source"><br></td></tr
><tr
id=sl_svn7768_919

><td class="source">      // convert the bitmap to an alpha channel<br></td></tr
><tr
id=sl_svn7768_920

><td class="source">      int w = width;<br></td></tr
><tr
id=sl_svn7768_921

><td class="source">      int h = height;<br></td></tr
><tr
id=sl_svn7768_922

><td class="source">      int[] pixels = image.pixels;<br></td></tr
><tr
id=sl_svn7768_923

><td class="source">      for (int y = 0; y &lt; h; y++) {<br></td></tr
><tr
id=sl_svn7768_924

><td class="source">        for (int x = 0; x &lt; w; x++) {<br></td></tr
><tr
id=sl_svn7768_925

><td class="source">          pixels[y * width + x] = temp[y*w + x] &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_926

><td class="source">//          System.out.print((image.pixels[y*64+x] &gt; 128) ? &quot;*&quot; : &quot;.&quot;);<br></td></tr
><tr
id=sl_svn7768_927

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_928

><td class="source">//        System.out.println();<br></td></tr
><tr
id=sl_svn7768_929

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_930

><td class="source">//      System.out.println();<br></td></tr
><tr
id=sl_svn7768_931

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_932

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_933

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_934

><td class="source">    protected void writeBitmap(DataOutputStream os) throws IOException {<br></td></tr
><tr
id=sl_svn7768_935

><td class="source">      int[] pixels  = image.pixels;<br></td></tr
><tr
id=sl_svn7768_936

><td class="source">      for (int y = 0; y &lt; height; y++) {<br></td></tr
><tr
id=sl_svn7768_937

><td class="source">        for (int x = 0; x &lt; width; x++) {<br></td></tr
><tr
id=sl_svn7768_938

><td class="source">          os.write(pixels[y * width + x] &amp; 0xff);<br></td></tr
><tr
id=sl_svn7768_939

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_940

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_941

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_942

><td class="source"><br></td></tr
><tr
id=sl_svn7768_943

><td class="source"><br></td></tr
><tr
id=sl_svn7768_944

><td class="source">    protected Glyph(char c) {<br></td></tr
><tr
id=sl_svn7768_945

><td class="source">      int mbox3 = size * 3;<br></td></tr
><tr
id=sl_svn7768_946

><td class="source">      lazyGraphics.setColor(Color.white);<br></td></tr
><tr
id=sl_svn7768_947

><td class="source">      lazyGraphics.fillRect(0, 0, mbox3, mbox3);<br></td></tr
><tr
id=sl_svn7768_948

><td class="source">      lazyGraphics.setColor(Color.black);<br></td></tr
><tr
id=sl_svn7768_949

><td class="source">      lazyGraphics.drawString(String.valueOf(c), size, size * 2);<br></td></tr
><tr
id=sl_svn7768_950

><td class="source"><br></td></tr
><tr
id=sl_svn7768_951

><td class="source">      WritableRaster raster = lazyImage.getRaster();<br></td></tr
><tr
id=sl_svn7768_952

><td class="source">      raster.getDataElements(0, 0, mbox3, mbox3, lazySamples);<br></td></tr
><tr
id=sl_svn7768_953

><td class="source"><br></td></tr
><tr
id=sl_svn7768_954

><td class="source">      int minX = 1000, maxX = 0;<br></td></tr
><tr
id=sl_svn7768_955

><td class="source">      int minY = 1000, maxY = 0;<br></td></tr
><tr
id=sl_svn7768_956

><td class="source">      boolean pixelFound = false;<br></td></tr
><tr
id=sl_svn7768_957

><td class="source"><br></td></tr
><tr
id=sl_svn7768_958

><td class="source">      for (int y = 0; y &lt; mbox3; y++) {<br></td></tr
><tr
id=sl_svn7768_959

><td class="source">        for (int x = 0; x &lt; mbox3; x++) {<br></td></tr
><tr
id=sl_svn7768_960

><td class="source">          int sample = lazySamples[y * mbox3 + x] &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_961

><td class="source">          if (sample != 255) {<br></td></tr
><tr
id=sl_svn7768_962

><td class="source">            if (x &lt; minX) minX = x;<br></td></tr
><tr
id=sl_svn7768_963

><td class="source">            if (y &lt; minY) minY = y;<br></td></tr
><tr
id=sl_svn7768_964

><td class="source">            if (x &gt; maxX) maxX = x;<br></td></tr
><tr
id=sl_svn7768_965

><td class="source">            if (y &gt; maxY) maxY = y;<br></td></tr
><tr
id=sl_svn7768_966

><td class="source">            pixelFound = true;<br></td></tr
><tr
id=sl_svn7768_967

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_968

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_969

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_970

><td class="source"><br></td></tr
><tr
id=sl_svn7768_971

><td class="source">      if (!pixelFound) {<br></td></tr
><tr
id=sl_svn7768_972

><td class="source">        minX = minY = 0;<br></td></tr
><tr
id=sl_svn7768_973

><td class="source">        maxX = maxY = 0;<br></td></tr
><tr
id=sl_svn7768_974

><td class="source">        // this will create a 1 pixel white (clear) character..<br></td></tr
><tr
id=sl_svn7768_975

><td class="source">        // maybe better to set one to -1 so nothing is added?<br></td></tr
><tr
id=sl_svn7768_976

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_977

><td class="source"><br></td></tr
><tr
id=sl_svn7768_978

><td class="source">      value = c;<br></td></tr
><tr
id=sl_svn7768_979

><td class="source">      height = (maxY - minY) + 1;<br></td></tr
><tr
id=sl_svn7768_980

><td class="source">      width = (maxX - minX) + 1;<br></td></tr
><tr
id=sl_svn7768_981

><td class="source">      setWidth = lazyMetrics.charWidth(c);<br></td></tr
><tr
id=sl_svn7768_982

><td class="source"><br></td></tr
><tr
id=sl_svn7768_983

><td class="source">      // offset from vertical location of baseline<br></td></tr
><tr
id=sl_svn7768_984

><td class="source">      // of where the char was drawn (size*2)<br></td></tr
><tr
id=sl_svn7768_985

><td class="source">      topExtent = size*2 - minY;<br></td></tr
><tr
id=sl_svn7768_986

><td class="source"><br></td></tr
><tr
id=sl_svn7768_987

><td class="source">      // offset from left of where coord was drawn<br></td></tr
><tr
id=sl_svn7768_988

><td class="source">      leftExtent = minX - size;<br></td></tr
><tr
id=sl_svn7768_989

><td class="source"><br></td></tr
><tr
id=sl_svn7768_990

><td class="source">      image = new PImage(width, height, ALPHA);<br></td></tr
><tr
id=sl_svn7768_991

><td class="source">      int[] pixels = image.pixels;<br></td></tr
><tr
id=sl_svn7768_992

><td class="source">      for (int y = minY; y &lt;= maxY; y++) {<br></td></tr
><tr
id=sl_svn7768_993

><td class="source">        for (int x = minX; x &lt;= maxX; x++) {<br></td></tr
><tr
id=sl_svn7768_994

><td class="source">          int val = 255 - (lazySamples[y * mbox3 + x] &amp; 0xff);<br></td></tr
><tr
id=sl_svn7768_995

><td class="source">          int pindex = (y - minY) * width + (x - minX);<br></td></tr
><tr
id=sl_svn7768_996

><td class="source">          pixels[pindex] = val;<br></td></tr
><tr
id=sl_svn7768_997

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_998

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_999

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1000

><td class="source">      // replace the ascent/descent values with something.. err, decent.<br></td></tr
><tr
id=sl_svn7768_1001

><td class="source">      if (value == &#39;d&#39;) {<br></td></tr
><tr
id=sl_svn7768_1002

><td class="source">        if (ascent == 0) ascent = topExtent;<br></td></tr
><tr
id=sl_svn7768_1003

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1004

><td class="source">      if (value == &#39;p&#39;) {<br></td></tr
><tr
id=sl_svn7768_1005

><td class="source">        if (descent == 0) descent = -topExtent + height;<br></td></tr
><tr
id=sl_svn7768_1006

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1007

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1008

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1009

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
 <a href="/p/processing/source/detail?spec=svn7768&r=7659">r7659</a>
 by andres.colubri
 on Feb 06, 2011
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7659&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PFont.java&amp;old_path=/trunk/processing/core/src/processing/core/PFont.java&amp;old=7647">Diff</a>
 </div>
 <pre>Removed PMetadata class</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/processing/source/detail?r=7659&spec=svn7768';
 var publish_url = '/p/processing/source/detail?r=7659&spec=svn7768#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PApplet.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PApplet.java?r\x3d7659\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PFont.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PFont.java?r\x3d7659\x26spec\x3dsvn7768');
 
 var selected_path = '/trunk/processing/core/src/processing/core/PFont.java';
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PGraphicsJava2D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphicsJava2D.java?r\x3d7659\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PImage.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PImage.java?r\x3d7659\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PMetadata.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PMetadata.java?r\x3d7659\x26spec\x3dsvn7768');
 
 
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
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PApplet.java?r=7659&amp;spec=svn7768"
 
 >...src/processing/core/PApplet.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PFont.java?r=7659&amp;spec=svn7768"
 selected="selected"
 >...e/src/processing/core/PFont.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphicsJava2D.java?r=7659&amp;spec=svn7768"
 
 >...essing/core/PGraphicsJava2D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PImage.java?r=7659&amp;spec=svn7768"
 
 >.../src/processing/core/PImage.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PMetadata.java?r=7659&amp;spec=svn7768"
 
 >...c/processing/core/PMetadata.java</option>
 
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
 <a href="/p/processing/source/detail?spec=svn7768&r=7647">r7647</a>
 by andres.colubri
 on Jan 31, 2011
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7647&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PFont.java&amp;old_path=/trunk/processing/core/src/processing/core/PFont.java&amp;old=7430">Diff</a>
 <br>
 <pre class="ifOpened">Merged-in the changes in the core
needed for the new opengl renderer</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=7430">r7430</a>
 by f...@processing.org
 on Nov 15, 2010
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7430&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PFont.java&amp;old_path=/trunk/processing/core/src/processing/core/PFont.java&amp;old=7149">Diff</a>
 <br>
 <pre class="ifOpened">add subsetting mode.. this needs a
better name
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=7149">r7149</a>
 by f...@processing.org
 on Aug 06, 2010
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7149&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PFont.java&amp;old_path=/trunk/processing/core/src/processing/core/PFont.java&amp;old=6644">Diff</a>
 <br>
 <pre class="ifOpened">working on how native fonts are
handled for better consistency
(incomplete)
</pre>
 </div>
 
 
 <a href="/p/processing/source/list?path=/trunk/processing/core/src/processing/core/PFont.java&start=7659">All revisions of this file</a>
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
 
 <div>Size: 30684 bytes,
 1009 lines</div>
 
 <div><a href="http://processing.googlecode.com/svn/trunk/processing/core/src/processing/core/PFont.java">View raw file</a></div>
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
 var paths = {'svn7768': '/trunk/processing/core/src/processing/core/PFont.java'}
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
 
 


 
 </body>
</html>

