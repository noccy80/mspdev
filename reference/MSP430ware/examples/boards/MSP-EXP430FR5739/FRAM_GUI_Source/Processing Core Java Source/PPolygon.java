



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 
 
 var codesite_token = "c6974bcd72eb95455827185f7306e1fa";
 
 
 var logged_in_user_email = "Dung.Dang@gmail.com";
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>PPolygon.java - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fprocessing%2Fsource%2Fbrowse%2Ftrunk%2Fprocessing%2Fcore%2Fsrc%2Fprocessing%2Fcore%2FPPolygon.java" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/processing/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/">core</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/">src</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/">core</a><span class="sp">/&nbsp;</span>PPolygon.java</span>
 
 

 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PPolygon.java?edit=1"
 ><img src="http://www.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PPolygon.java?r=5483" title="Previous">&lsaquo;r5483</a></li>
 
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

><td class="source">  Copyright (c) 2004-08 Ben Fry and Casey Reas<br></td></tr
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

><td class="source">  modify it under the terms of the GNU Lesser General Public<br></td></tr
><tr
id=sl_svn7768_11

><td class="source">  License as published by the Free Software Foundation; either<br></td></tr
><tr
id=sl_svn7768_12

><td class="source">  version 2.1 of the License, or (at your option) any later version.<br></td></tr
><tr
id=sl_svn7768_13

><td class="source"><br></td></tr
><tr
id=sl_svn7768_14

><td class="source">  This library is distributed in the hope that it will be useful,<br></td></tr
><tr
id=sl_svn7768_15

><td class="source">  but WITHOUT ANY WARRANTY; without even the implied warranty of<br></td></tr
><tr
id=sl_svn7768_16

><td class="source">  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU<br></td></tr
><tr
id=sl_svn7768_17

><td class="source">  Lesser General Public License for more details.<br></td></tr
><tr
id=sl_svn7768_18

><td class="source"><br></td></tr
><tr
id=sl_svn7768_19

><td class="source">  You should have received a copy of the GNU Lesser General<br></td></tr
><tr
id=sl_svn7768_20

><td class="source">  Public License along with this library; if not, write to the<br></td></tr
><tr
id=sl_svn7768_21

><td class="source">  Free Software Foundation, Inc., 59 Temple Place, Suite 330,<br></td></tr
><tr
id=sl_svn7768_22

><td class="source">  Boston, MA  02111-1307  USA<br></td></tr
><tr
id=sl_svn7768_23

><td class="source">*/<br></td></tr
><tr
id=sl_svn7768_24

><td class="source"><br></td></tr
><tr
id=sl_svn7768_25

><td class="source">package processing.core;<br></td></tr
><tr
id=sl_svn7768_26

><td class="source"><br></td></tr
><tr
id=sl_svn7768_27

><td class="source"><br></td></tr
><tr
id=sl_svn7768_28

><td class="source">/**<br></td></tr
><tr
id=sl_svn7768_29

><td class="source"> * Z-buffer polygon rendering object used by PGraphics2D.<br></td></tr
><tr
id=sl_svn7768_30

><td class="source"> */<br></td></tr
><tr
id=sl_svn7768_31

><td class="source">public class PPolygon implements PConstants {<br></td></tr
><tr
id=sl_svn7768_32

><td class="source"><br></td></tr
><tr
id=sl_svn7768_33

><td class="source">  static final int DEFAULT_SIZE = 64; // this is needed for spheres<br></td></tr
><tr
id=sl_svn7768_34

><td class="source">  float vertices[][] = new float[DEFAULT_SIZE][VERTEX_FIELD_COUNT];<br></td></tr
><tr
id=sl_svn7768_35

><td class="source">  int vertexCount;<br></td></tr
><tr
id=sl_svn7768_36

><td class="source"><br></td></tr
><tr
id=sl_svn7768_37

><td class="source">  float r[]   = new float[DEFAULT_SIZE]; // storage used by incrementalize<br></td></tr
><tr
id=sl_svn7768_38

><td class="source">  float dr[]  = new float[DEFAULT_SIZE];<br></td></tr
><tr
id=sl_svn7768_39

><td class="source">  float l[]   = new float[DEFAULT_SIZE]; // more storage for incrementalize<br></td></tr
><tr
id=sl_svn7768_40

><td class="source">  float dl[]  = new float[DEFAULT_SIZE];<br></td></tr
><tr
id=sl_svn7768_41

><td class="source">  float sp[]  = new float[DEFAULT_SIZE]; // temporary storage for scanline<br></td></tr
><tr
id=sl_svn7768_42

><td class="source">  float sdp[] = new float[DEFAULT_SIZE];<br></td></tr
><tr
id=sl_svn7768_43

><td class="source"><br></td></tr
><tr
id=sl_svn7768_44

><td class="source">  protected boolean interpX;<br></td></tr
><tr
id=sl_svn7768_45

><td class="source">  protected boolean interpUV; // is this necessary? could just check timage != null<br></td></tr
><tr
id=sl_svn7768_46

><td class="source">  protected boolean interpARGB;<br></td></tr
><tr
id=sl_svn7768_47

><td class="source"><br></td></tr
><tr
id=sl_svn7768_48

><td class="source">  private int rgba;<br></td></tr
><tr
id=sl_svn7768_49

><td class="source">  private int r2, g2, b2, a2, a2orig;<br></td></tr
><tr
id=sl_svn7768_50

><td class="source"><br></td></tr
><tr
id=sl_svn7768_51

><td class="source">  PGraphics parent;<br></td></tr
><tr
id=sl_svn7768_52

><td class="source">  int[] pixels;<br></td></tr
><tr
id=sl_svn7768_53

><td class="source">  // the parent&#39;s width/height,<br></td></tr
><tr
id=sl_svn7768_54

><td class="source">  // or if smooth is enabled, parent&#39;s w/h scaled<br></td></tr
><tr
id=sl_svn7768_55

><td class="source">  // up by the smooth dimension<br></td></tr
><tr
id=sl_svn7768_56

><td class="source">  int width, height;<br></td></tr
><tr
id=sl_svn7768_57

><td class="source">  int width1, height1;<br></td></tr
><tr
id=sl_svn7768_58

><td class="source"><br></td></tr
><tr
id=sl_svn7768_59

><td class="source">  PImage timage;<br></td></tr
><tr
id=sl_svn7768_60

><td class="source">  int[] tpixels;<br></td></tr
><tr
id=sl_svn7768_61

><td class="source">  int theight, twidth;<br></td></tr
><tr
id=sl_svn7768_62

><td class="source">  int theight1, twidth1;<br></td></tr
><tr
id=sl_svn7768_63

><td class="source">  int tformat;<br></td></tr
><tr
id=sl_svn7768_64

><td class="source"><br></td></tr
><tr
id=sl_svn7768_65

><td class="source">  // for anti-aliasing<br></td></tr
><tr
id=sl_svn7768_66

><td class="source">  static final int SUBXRES  = 8;<br></td></tr
><tr
id=sl_svn7768_67

><td class="source">  static final int SUBXRES1 = 7;<br></td></tr
><tr
id=sl_svn7768_68

><td class="source">  static final int SUBYRES  = 8;<br></td></tr
><tr
id=sl_svn7768_69

><td class="source">  static final int SUBYRES1 = 7;<br></td></tr
><tr
id=sl_svn7768_70

><td class="source">  static final int MAX_COVERAGE = SUBXRES * SUBYRES;<br></td></tr
><tr
id=sl_svn7768_71

><td class="source"><br></td></tr
><tr
id=sl_svn7768_72

><td class="source">  boolean smooth;<br></td></tr
><tr
id=sl_svn7768_73

><td class="source">  int firstModY;<br></td></tr
><tr
id=sl_svn7768_74

><td class="source">  int lastModY;<br></td></tr
><tr
id=sl_svn7768_75

><td class="source">  int lastY;<br></td></tr
><tr
id=sl_svn7768_76

><td class="source">  int aaleft[] = new int[SUBYRES];<br></td></tr
><tr
id=sl_svn7768_77

><td class="source">  int aaright[] = new int[SUBYRES];<br></td></tr
><tr
id=sl_svn7768_78

><td class="source">  int aaleftmin, aarightmin;<br></td></tr
><tr
id=sl_svn7768_79

><td class="source">  int aaleftmax, aarightmax;<br></td></tr
><tr
id=sl_svn7768_80

><td class="source">  int aaleftfull, aarightfull;<br></td></tr
><tr
id=sl_svn7768_81

><td class="source"><br></td></tr
><tr
id=sl_svn7768_82

><td class="source">  final private int MODYRES(int y) {<br></td></tr
><tr
id=sl_svn7768_83

><td class="source">    return (y &amp; SUBYRES1);<br></td></tr
><tr
id=sl_svn7768_84

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_85

><td class="source"><br></td></tr
><tr
id=sl_svn7768_86

><td class="source"><br></td></tr
><tr
id=sl_svn7768_87

><td class="source">  public PPolygon(PGraphics iparent) {<br></td></tr
><tr
id=sl_svn7768_88

><td class="source">    parent = iparent;<br></td></tr
><tr
id=sl_svn7768_89

><td class="source">    reset(0);<br></td></tr
><tr
id=sl_svn7768_90

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_91

><td class="source"><br></td></tr
><tr
id=sl_svn7768_92

><td class="source"><br></td></tr
><tr
id=sl_svn7768_93

><td class="source">  protected void reset(int count) {<br></td></tr
><tr
id=sl_svn7768_94

><td class="source">    vertexCount = count;<br></td></tr
><tr
id=sl_svn7768_95

><td class="source">    interpX = true;<br></td></tr
><tr
id=sl_svn7768_96

><td class="source">//    interpZ = true;<br></td></tr
><tr
id=sl_svn7768_97

><td class="source">    interpUV = false;<br></td></tr
><tr
id=sl_svn7768_98

><td class="source">    interpARGB = true;<br></td></tr
><tr
id=sl_svn7768_99

><td class="source">    timage = null;<br></td></tr
><tr
id=sl_svn7768_100

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_101

><td class="source"><br></td></tr
><tr
id=sl_svn7768_102

><td class="source"><br></td></tr
><tr
id=sl_svn7768_103

><td class="source">  protected float[] nextVertex() {<br></td></tr
><tr
id=sl_svn7768_104

><td class="source">    if (vertexCount == vertices.length) {<br></td></tr
><tr
id=sl_svn7768_105

><td class="source">      float temp[][] = new float[vertexCount&lt;&lt;1][VERTEX_FIELD_COUNT];<br></td></tr
><tr
id=sl_svn7768_106

><td class="source">      System.arraycopy(vertices, 0, temp, 0, vertexCount);<br></td></tr
><tr
id=sl_svn7768_107

><td class="source">      vertices = temp;<br></td></tr
><tr
id=sl_svn7768_108

><td class="source"><br></td></tr
><tr
id=sl_svn7768_109

><td class="source">      r   = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_110

><td class="source">      dr  = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_111

><td class="source">      l   = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_112

><td class="source">      dl  = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_113

><td class="source">      sp  = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_114

><td class="source">      sdp = new float[vertices.length];<br></td></tr
><tr
id=sl_svn7768_115

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_116

><td class="source">    return vertices[vertexCount++];  // returns v[0], sets vc to 1<br></td></tr
><tr
id=sl_svn7768_117

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_118

><td class="source"><br></td></tr
><tr
id=sl_svn7768_119

><td class="source"><br></td></tr
><tr
id=sl_svn7768_120

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_121

><td class="source">   * Return true if this vertex is redundant. If so, will also<br></td></tr
><tr
id=sl_svn7768_122

><td class="source">   * decrement the vertex count.<br></td></tr
><tr
id=sl_svn7768_123

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_124

><td class="source">  /*<br></td></tr
><tr
id=sl_svn7768_125

><td class="source">  public boolean redundantVertex(float x, float y, float z) {<br></td></tr
><tr
id=sl_svn7768_126

><td class="source">    // because vertexCount will be 2 when setting vertex[1]<br></td></tr
><tr
id=sl_svn7768_127

><td class="source">    if (vertexCount &lt; 2) return false;<br></td></tr
><tr
id=sl_svn7768_128

><td class="source"><br></td></tr
><tr
id=sl_svn7768_129

><td class="source">    // vertexCount-1 is the current vertex that would be used<br></td></tr
><tr
id=sl_svn7768_130

><td class="source">    // vertexCount-2 would be the previous feller<br></td></tr
><tr
id=sl_svn7768_131

><td class="source">    if ((Math.abs(vertices[vertexCount-2][MX] - x) &lt; EPSILON) &amp;&amp;<br></td></tr
><tr
id=sl_svn7768_132

><td class="source">        (Math.abs(vertices[vertexCount-2][MY] - y) &lt; EPSILON) &amp;&amp;<br></td></tr
><tr
id=sl_svn7768_133

><td class="source">        (Math.abs(vertices[vertexCount-2][MZ] - z) &lt; EPSILON)) {<br></td></tr
><tr
id=sl_svn7768_134

><td class="source">      vertexCount--;<br></td></tr
><tr
id=sl_svn7768_135

><td class="source">      return true;<br></td></tr
><tr
id=sl_svn7768_136

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_137

><td class="source">    return false;<br></td></tr
><tr
id=sl_svn7768_138

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_139

><td class="source">  */<br></td></tr
><tr
id=sl_svn7768_140

><td class="source"><br></td></tr
><tr
id=sl_svn7768_141

><td class="source"><br></td></tr
><tr
id=sl_svn7768_142

><td class="source">  protected void texture(PImage image) {<br></td></tr
><tr
id=sl_svn7768_143

><td class="source">    this.timage = image;<br></td></tr
><tr
id=sl_svn7768_144

><td class="source"><br></td></tr
><tr
id=sl_svn7768_145

><td class="source">    if (image != null) {<br></td></tr
><tr
id=sl_svn7768_146

><td class="source">      this.tpixels = image.pixels;<br></td></tr
><tr
id=sl_svn7768_147

><td class="source">      this.twidth = image.width;<br></td></tr
><tr
id=sl_svn7768_148

><td class="source">      this.theight = image.height;<br></td></tr
><tr
id=sl_svn7768_149

><td class="source">      this.tformat = image.format;<br></td></tr
><tr
id=sl_svn7768_150

><td class="source"><br></td></tr
><tr
id=sl_svn7768_151

><td class="source">      twidth1 = twidth - 1;<br></td></tr
><tr
id=sl_svn7768_152

><td class="source">      theight1 = theight - 1;<br></td></tr
><tr
id=sl_svn7768_153

><td class="source">      interpUV = true;<br></td></tr
><tr
id=sl_svn7768_154

><td class="source">      <br></td></tr
><tr
id=sl_svn7768_155

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_156

><td class="source">      interpUV = false;      <br></td></tr
><tr
id=sl_svn7768_157

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_158

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_159

><td class="source"><br></td></tr
><tr
id=sl_svn7768_160

><td class="source"><br></td></tr
><tr
id=sl_svn7768_161

><td class="source">  protected void renderPolygon(float[][] v, int count) {<br></td></tr
><tr
id=sl_svn7768_162

><td class="source">    vertices = v;<br></td></tr
><tr
id=sl_svn7768_163

><td class="source">    vertexCount = count;<br></td></tr
><tr
id=sl_svn7768_164

><td class="source"><br></td></tr
><tr
id=sl_svn7768_165

><td class="source">    if (r.length &lt; vertexCount) {<br></td></tr
><tr
id=sl_svn7768_166

><td class="source">      r   = new float[vertexCount]; // storage used by incrementalize<br></td></tr
><tr
id=sl_svn7768_167

><td class="source">      dr  = new float[vertexCount];<br></td></tr
><tr
id=sl_svn7768_168

><td class="source">      l   = new float[vertexCount]; // more storage for incrementalize<br></td></tr
><tr
id=sl_svn7768_169

><td class="source">      dl  = new float[vertexCount];<br></td></tr
><tr
id=sl_svn7768_170

><td class="source">      sp  = new float[vertexCount]; // temporary storage for scanline<br></td></tr
><tr
id=sl_svn7768_171

><td class="source">      sdp = new float[vertexCount];<br></td></tr
><tr
id=sl_svn7768_172

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_173

><td class="source"><br></td></tr
><tr
id=sl_svn7768_174

><td class="source">    render();<br></td></tr
><tr
id=sl_svn7768_175

><td class="source">    checkExpand();<br></td></tr
><tr
id=sl_svn7768_176

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_177

><td class="source"><br></td></tr
><tr
id=sl_svn7768_178

><td class="source"><br></td></tr
><tr
id=sl_svn7768_179

><td class="source">  protected void renderTriangle(float[] v1, float[] v2, float[] v3) {<br></td></tr
><tr
id=sl_svn7768_180

><td class="source">    // Calling code will have already done reset(3).<br></td></tr
><tr
id=sl_svn7768_181

><td class="source">    // Can&#39;t do it here otherwise would nuke any texture settings.<br></td></tr
><tr
id=sl_svn7768_182

><td class="source"><br></td></tr
><tr
id=sl_svn7768_183

><td class="source">    vertices[0] = v1;<br></td></tr
><tr
id=sl_svn7768_184

><td class="source">    vertices[1] = v2;<br></td></tr
><tr
id=sl_svn7768_185

><td class="source">    vertices[2] = v3;<br></td></tr
><tr
id=sl_svn7768_186

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_187

><td class="source">    render();<br></td></tr
><tr
id=sl_svn7768_188

><td class="source">    checkExpand();<br></td></tr
><tr
id=sl_svn7768_189

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_190

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_191

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_192

><td class="source">  protected void checkExpand() {<br></td></tr
><tr
id=sl_svn7768_193

><td class="source">    if (smooth) {<br></td></tr
><tr
id=sl_svn7768_194

><td class="source">      for (int i = 0; i &lt; vertexCount; i++) {<br></td></tr
><tr
id=sl_svn7768_195

><td class="source">        vertices[i][TX] /= SUBXRES;<br></td></tr
><tr
id=sl_svn7768_196

><td class="source">        vertices[i][TY] /= SUBYRES;<br></td></tr
><tr
id=sl_svn7768_197

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_198

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_199

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_200

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_201

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_202

><td class="source">  protected void render() {<br></td></tr
><tr
id=sl_svn7768_203

><td class="source">    if (vertexCount &lt; 3) return;<br></td></tr
><tr
id=sl_svn7768_204

><td class="source"><br></td></tr
><tr
id=sl_svn7768_205

><td class="source">    // these may have changed due to a resize()<br></td></tr
><tr
id=sl_svn7768_206

><td class="source">    // so they should be refreshed here<br></td></tr
><tr
id=sl_svn7768_207

><td class="source">    pixels = parent.pixels;<br></td></tr
><tr
id=sl_svn7768_208

><td class="source">    //zbuffer = parent.zbuffer;<br></td></tr
><tr
id=sl_svn7768_209

><td class="source"><br></td></tr
><tr
id=sl_svn7768_210

><td class="source">//    noDepthTest = parent.hints[DISABLE_DEPTH_TEST];<br></td></tr
><tr
id=sl_svn7768_211

><td class="source">    smooth = parent.smooth;<br></td></tr
><tr
id=sl_svn7768_212

><td class="source"><br></td></tr
><tr
id=sl_svn7768_213

><td class="source">    // by default, text turns on smooth for the textures<br></td></tr
><tr
id=sl_svn7768_214

><td class="source">    // themselves. but this should be shut off if the hint<br></td></tr
><tr
id=sl_svn7768_215

><td class="source">    // for DISABLE_TEXT_SMOOTH is set.<br></td></tr
><tr
id=sl_svn7768_216

><td class="source">//    texture_smooth = true;<br></td></tr
><tr
id=sl_svn7768_217

><td class="source"><br></td></tr
><tr
id=sl_svn7768_218

><td class="source">    width = smooth ? parent.width*SUBXRES : parent.width;<br></td></tr
><tr
id=sl_svn7768_219

><td class="source">    height = smooth ? parent.height*SUBYRES : parent.height;<br></td></tr
><tr
id=sl_svn7768_220

><td class="source"><br></td></tr
><tr
id=sl_svn7768_221

><td class="source">    width1 = width - 1;<br></td></tr
><tr
id=sl_svn7768_222

><td class="source">    height1 = height - 1;<br></td></tr
><tr
id=sl_svn7768_223

><td class="source"><br></td></tr
><tr
id=sl_svn7768_224

><td class="source">    if (!interpARGB) {<br></td></tr
><tr
id=sl_svn7768_225

><td class="source">      r2 = (int) (vertices[0][R] * 255);<br></td></tr
><tr
id=sl_svn7768_226

><td class="source">      g2 = (int) (vertices[0][G] * 255);<br></td></tr
><tr
id=sl_svn7768_227

><td class="source">      b2 = (int) (vertices[0][B] * 255);<br></td></tr
><tr
id=sl_svn7768_228

><td class="source">      a2 = (int) (vertices[0][A] * 255);<br></td></tr
><tr
id=sl_svn7768_229

><td class="source">      a2orig = a2; // save an extra copy<br></td></tr
><tr
id=sl_svn7768_230

><td class="source">      rgba = 0xff000000 | (r2 &lt;&lt; 16) | (g2 &lt;&lt; 8) | b2;<br></td></tr
><tr
id=sl_svn7768_231

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_232

><td class="source"><br></td></tr
><tr
id=sl_svn7768_233

><td class="source">    for (int i = 0; i &lt; vertexCount; i++) {<br></td></tr
><tr
id=sl_svn7768_234

><td class="source">      r[i] = 0; dr[i] = 0; l[i] = 0; dl[i] = 0;<br></td></tr
><tr
id=sl_svn7768_235

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_236

><td class="source"><br></td></tr
><tr
id=sl_svn7768_237

><td class="source">    /*<br></td></tr
><tr
id=sl_svn7768_238

><td class="source">    // hack to not make polygons fly into the screen<br></td></tr
><tr
id=sl_svn7768_239

><td class="source">    if (parent.hints[DISABLE_FLYING_POO]) {<br></td></tr
><tr
id=sl_svn7768_240

><td class="source">      float nwidth2 = -width * 2;<br></td></tr
><tr
id=sl_svn7768_241

><td class="source">      float nheight2 = -height * 2;<br></td></tr
><tr
id=sl_svn7768_242

><td class="source">      float width2 = width * 2;<br></td></tr
><tr
id=sl_svn7768_243

><td class="source">      float height2 = height * 2;<br></td></tr
><tr
id=sl_svn7768_244

><td class="source">      for (int i = 0; i &lt; vertexCount; i++) {<br></td></tr
><tr
id=sl_svn7768_245

><td class="source">        if ((vertices[i][TX] &lt; nwidth2) ||<br></td></tr
><tr
id=sl_svn7768_246

><td class="source">            (vertices[i][TX] &gt; width2) ||<br></td></tr
><tr
id=sl_svn7768_247

><td class="source">            (vertices[i][TY] &lt; nheight2) ||<br></td></tr
><tr
id=sl_svn7768_248

><td class="source">            (vertices[i][TY] &gt; height2)) {<br></td></tr
><tr
id=sl_svn7768_249

><td class="source">          return;  // this is a bad poly<br></td></tr
><tr
id=sl_svn7768_250

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_251

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_252

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_253

><td class="source">    */<br></td></tr
><tr
id=sl_svn7768_254

><td class="source"><br></td></tr
><tr
id=sl_svn7768_255

><td class="source">//    for (int i = 0; i &lt; 4; i++) {<br></td></tr
><tr
id=sl_svn7768_256

><td class="source">//      System.out.println(vertices[i][R] + &quot; &quot; + vertices[i][G] + &quot; &quot; + vertices[i][B]);<br></td></tr
><tr
id=sl_svn7768_257

><td class="source">//    }<br></td></tr
><tr
id=sl_svn7768_258

><td class="source">//    System.out.println();<br></td></tr
><tr
id=sl_svn7768_259

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_260

><td class="source">    if (smooth) {<br></td></tr
><tr
id=sl_svn7768_261

><td class="source">      for (int i = 0; i &lt; vertexCount; i++) {<br></td></tr
><tr
id=sl_svn7768_262

><td class="source">        vertices[i][TX] *= SUBXRES;<br></td></tr
><tr
id=sl_svn7768_263

><td class="source">        vertices[i][TY] *= SUBYRES;<br></td></tr
><tr
id=sl_svn7768_264

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_265

><td class="source">      firstModY = -1;<br></td></tr
><tr
id=sl_svn7768_266

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_267

><td class="source"><br></td></tr
><tr
id=sl_svn7768_268

><td class="source">    // find top vertex (y is zero at top, higher downwards)<br></td></tr
><tr
id=sl_svn7768_269

><td class="source">    int topi = 0;<br></td></tr
><tr
id=sl_svn7768_270

><td class="source">    float ymin = vertices[0][TY];<br></td></tr
><tr
id=sl_svn7768_271

><td class="source">    float ymax = vertices[0][TY]; // fry 031001<br></td></tr
><tr
id=sl_svn7768_272

><td class="source">    for (int i = 1; i &lt; vertexCount; i++) {<br></td></tr
><tr
id=sl_svn7768_273

><td class="source">      if (vertices[i][TY] &lt; ymin) {<br></td></tr
><tr
id=sl_svn7768_274

><td class="source">        ymin = vertices[i][TY];<br></td></tr
><tr
id=sl_svn7768_275

><td class="source">        topi = i;<br></td></tr
><tr
id=sl_svn7768_276

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_277

><td class="source">      if (vertices[i][TY] &gt; ymax) {<br></td></tr
><tr
id=sl_svn7768_278

><td class="source">        ymax = vertices[i][TY];<br></td></tr
><tr
id=sl_svn7768_279

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_280

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_281

><td class="source"><br></td></tr
><tr
id=sl_svn7768_282

><td class="source">    // the last row is an exceptional case, because there won&#39;t<br></td></tr
><tr
id=sl_svn7768_283

><td class="source">    // necessarily be 8 rows of subpixel lines that will force<br></td></tr
><tr
id=sl_svn7768_284

><td class="source">    // the final line to render. so instead, the algo keeps track<br></td></tr
><tr
id=sl_svn7768_285

><td class="source">    // of the lastY (in subpixel resolution) that will be rendered<br></td></tr
><tr
id=sl_svn7768_286

><td class="source">    // and that will force a scanline to happen the same as<br></td></tr
><tr
id=sl_svn7768_287

><td class="source">    // every eighth in the other situations<br></td></tr
><tr
id=sl_svn7768_288

><td class="source">    //lastY = -1;  // fry 031001<br></td></tr
><tr
id=sl_svn7768_289

><td class="source">    lastY = (int) (ymax - 0.5f);  // global to class bc used by other fxns<br></td></tr
><tr
id=sl_svn7768_290

><td class="source"><br></td></tr
><tr
id=sl_svn7768_291

><td class="source">    int lefti = topi;             // li, index of left vertex<br></td></tr
><tr
id=sl_svn7768_292

><td class="source">    int righti = topi;            // ri, index of right vertex<br></td></tr
><tr
id=sl_svn7768_293

><td class="source">    int y = (int) (ymin + 0.5f);  // current scan line<br></td></tr
><tr
id=sl_svn7768_294

><td class="source">    int lefty = y - 1;            // lower end of left edge<br></td></tr
><tr
id=sl_svn7768_295

><td class="source">    int righty = y - 1;           // lower end of right edge<br></td></tr
><tr
id=sl_svn7768_296

><td class="source"><br></td></tr
><tr
id=sl_svn7768_297

><td class="source">    interpX = true;<br></td></tr
><tr
id=sl_svn7768_298

><td class="source"><br></td></tr
><tr
id=sl_svn7768_299

><td class="source">    int remaining = vertexCount;<br></td></tr
><tr
id=sl_svn7768_300

><td class="source"><br></td></tr
><tr
id=sl_svn7768_301

><td class="source">    // scan in y, activating new edges on left &amp; right<br></td></tr
><tr
id=sl_svn7768_302

><td class="source">    // as scan line passes over new vertices<br></td></tr
><tr
id=sl_svn7768_303

><td class="source">    while (remaining &gt; 0) {<br></td></tr
><tr
id=sl_svn7768_304

><td class="source">      // advance left edge?<br></td></tr
><tr
id=sl_svn7768_305

><td class="source">      while ((lefty &lt;= y) &amp;&amp; (remaining &gt; 0)) {<br></td></tr
><tr
id=sl_svn7768_306

><td class="source">        remaining--;<br></td></tr
><tr
id=sl_svn7768_307

><td class="source">        // step ccw down left side<br></td></tr
><tr
id=sl_svn7768_308

><td class="source">        int i = (lefti != 0) ? (lefti-1) : (vertexCount-1);<br></td></tr
><tr
id=sl_svn7768_309

><td class="source">        incrementalizeY(vertices[lefti], vertices[i], l, dl, y);<br></td></tr
><tr
id=sl_svn7768_310

><td class="source">        lefty = (int) (vertices[i][TY] + 0.5f);<br></td></tr
><tr
id=sl_svn7768_311

><td class="source">        lefti = i;<br></td></tr
><tr
id=sl_svn7768_312

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_313

><td class="source"><br></td></tr
><tr
id=sl_svn7768_314

><td class="source">      // advance right edge?<br></td></tr
><tr
id=sl_svn7768_315

><td class="source">      while ((righty &lt;= y) &amp;&amp; (remaining &gt; 0)) {<br></td></tr
><tr
id=sl_svn7768_316

><td class="source">        remaining--;<br></td></tr
><tr
id=sl_svn7768_317

><td class="source">        // step cw down right edge<br></td></tr
><tr
id=sl_svn7768_318

><td class="source">        int i = (righti != vertexCount-1) ? (righti + 1) : 0;<br></td></tr
><tr
id=sl_svn7768_319

><td class="source">        incrementalizeY(vertices[righti], vertices[i], r, dr, y);<br></td></tr
><tr
id=sl_svn7768_320

><td class="source">        righty = (int) (vertices[i][TY] + 0.5f);<br></td></tr
><tr
id=sl_svn7768_321

><td class="source">        righti = i;<br></td></tr
><tr
id=sl_svn7768_322

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_323

><td class="source"><br></td></tr
><tr
id=sl_svn7768_324

><td class="source">      // do scanlines till end of l or r edge<br></td></tr
><tr
id=sl_svn7768_325

><td class="source">      while (y &lt; lefty &amp;&amp; y &lt; righty) {<br></td></tr
><tr
id=sl_svn7768_326

><td class="source">        // this doesn&#39;t work because it&#39;s not always set here<br></td></tr
><tr
id=sl_svn7768_327

><td class="source">        //if (remaining == 0) {<br></td></tr
><tr
id=sl_svn7768_328

><td class="source">        //lastY = (lefty &lt; righty) ? lefty-1 : righty-1;<br></td></tr
><tr
id=sl_svn7768_329

><td class="source">        //System.out.println(&quot;lastY is &quot; + lastY);<br></td></tr
><tr
id=sl_svn7768_330

><td class="source">        //}<br></td></tr
><tr
id=sl_svn7768_331

><td class="source"><br></td></tr
><tr
id=sl_svn7768_332

><td class="source">        if ((y &gt;= 0) &amp;&amp; (y &lt; height)) {<br></td></tr
><tr
id=sl_svn7768_333

><td class="source">          //try {  // hopefully this bug is fixed<br></td></tr
><tr
id=sl_svn7768_334

><td class="source">          if (l[TX] &lt;= r[TX]) scanline(y, l, r);<br></td></tr
><tr
id=sl_svn7768_335

><td class="source">          else scanline(y, r, l);<br></td></tr
><tr
id=sl_svn7768_336

><td class="source">          //} catch (ArrayIndexOutOfBoundsException e) {<br></td></tr
><tr
id=sl_svn7768_337

><td class="source">          //e.printStackTrace();<br></td></tr
><tr
id=sl_svn7768_338

><td class="source">          //}<br></td></tr
><tr
id=sl_svn7768_339

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_340

><td class="source">        y++;<br></td></tr
><tr
id=sl_svn7768_341

><td class="source">        // this increment probably needs to be different<br></td></tr
><tr
id=sl_svn7768_342

><td class="source">        // UV and RGB shouldn&#39;t be incremented until line is emitted<br></td></tr
><tr
id=sl_svn7768_343

><td class="source">        increment(l, dl);<br></td></tr
><tr
id=sl_svn7768_344

><td class="source">        increment(r, dr);<br></td></tr
><tr
id=sl_svn7768_345

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_346

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_347

><td class="source">    //if (smooth) {<br></td></tr
><tr
id=sl_svn7768_348

><td class="source">    //System.out.println(&quot;y/lasty/lastmody = &quot; + y + &quot; &quot; + lastY + &quot; &quot; + lastModY);<br></td></tr
><tr
id=sl_svn7768_349

><td class="source">    //}<br></td></tr
><tr
id=sl_svn7768_350

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_351

><td class="source"><br></td></tr
><tr
id=sl_svn7768_352

><td class="source"><br></td></tr
><tr
id=sl_svn7768_353

><td class="source">  private void scanline(int y, float l[], float r[]) {<br></td></tr
><tr
id=sl_svn7768_354

><td class="source">    //System.out.println(&quot;scanline &quot; + y);<br></td></tr
><tr
id=sl_svn7768_355

><td class="source">    for (int i = 0; i &lt; vertexCount; i++) {  // should be moved later<br></td></tr
><tr
id=sl_svn7768_356

><td class="source">      sp[i] = 0; sdp[i] = 0;<br></td></tr
><tr
id=sl_svn7768_357

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_358

><td class="source"><br></td></tr
><tr
id=sl_svn7768_359

><td class="source">    // this rounding doesn&#39;t seem to be relevant with smooth<br></td></tr
><tr
id=sl_svn7768_360

><td class="source">    int lx = (int) (l[TX] + 0.49999f);  // ceil(l[TX]-.5);<br></td></tr
><tr
id=sl_svn7768_361

><td class="source">    if (lx &lt; 0) lx = 0;<br></td></tr
><tr
id=sl_svn7768_362

><td class="source">    int rx = (int) (r[TX] - 0.5f);<br></td></tr
><tr
id=sl_svn7768_363

><td class="source">    if (rx &gt; width1) rx = width1;<br></td></tr
><tr
id=sl_svn7768_364

><td class="source"><br></td></tr
><tr
id=sl_svn7768_365

><td class="source">    if (lx &gt; rx) return;<br></td></tr
><tr
id=sl_svn7768_366

><td class="source"><br></td></tr
><tr
id=sl_svn7768_367

><td class="source">    if (smooth) {<br></td></tr
><tr
id=sl_svn7768_368

><td class="source">      int mody = MODYRES(y);<br></td></tr
><tr
id=sl_svn7768_369

><td class="source"><br></td></tr
><tr
id=sl_svn7768_370

><td class="source">      aaleft[mody] = lx;<br></td></tr
><tr
id=sl_svn7768_371

><td class="source">      aaright[mody] = rx;<br></td></tr
><tr
id=sl_svn7768_372

><td class="source"><br></td></tr
><tr
id=sl_svn7768_373

><td class="source">      if (firstModY == -1) {<br></td></tr
><tr
id=sl_svn7768_374

><td class="source">        firstModY = mody;<br></td></tr
><tr
id=sl_svn7768_375

><td class="source">        aaleftmin = lx; aaleftmax = lx;<br></td></tr
><tr
id=sl_svn7768_376

><td class="source">        aarightmin = rx; aarightmax = rx;<br></td></tr
><tr
id=sl_svn7768_377

><td class="source"><br></td></tr
><tr
id=sl_svn7768_378

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_379

><td class="source">        if (aaleftmin &gt; aaleft[mody]) aaleftmin = aaleft[mody];<br></td></tr
><tr
id=sl_svn7768_380

><td class="source">        if (aaleftmax &lt; aaleft[mody]) aaleftmax = aaleft[mody];<br></td></tr
><tr
id=sl_svn7768_381

><td class="source">        if (aarightmin &gt; aaright[mody]) aarightmin = aaright[mody];<br></td></tr
><tr
id=sl_svn7768_382

><td class="source">        if (aarightmax &lt; aaright[mody]) aarightmax = aaright[mody];<br></td></tr
><tr
id=sl_svn7768_383

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_384

><td class="source"><br></td></tr
><tr
id=sl_svn7768_385

><td class="source">      lastModY = mody;  // moved up here (before the return) 031001<br></td></tr
><tr
id=sl_svn7768_386

><td class="source">      // not the eighth (or lastY) line, so not scanning this time<br></td></tr
><tr
id=sl_svn7768_387

><td class="source">      if ((mody != SUBYRES1) &amp;&amp; (y != lastY)) return;<br></td></tr
><tr
id=sl_svn7768_388

><td class="source">        //lastModY = mody;  // eeK! this was missing<br></td></tr
><tr
id=sl_svn7768_389

><td class="source">      //return;<br></td></tr
><tr
id=sl_svn7768_390

><td class="source"><br></td></tr
><tr
id=sl_svn7768_391

><td class="source">      //if (y == lastY) {<br></td></tr
><tr
id=sl_svn7768_392

><td class="source">      //System.out.println(&quot;y is lasty&quot;);<br></td></tr
><tr
id=sl_svn7768_393

><td class="source">      //}<br></td></tr
><tr
id=sl_svn7768_394

><td class="source">      //lastModY = mody;<br></td></tr
><tr
id=sl_svn7768_395

><td class="source">      aaleftfull = aaleftmax/SUBXRES + 1;<br></td></tr
><tr
id=sl_svn7768_396

><td class="source">      aarightfull = aarightmin/SUBXRES - 1;<br></td></tr
><tr
id=sl_svn7768_397

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_398

><td class="source"><br></td></tr
><tr
id=sl_svn7768_399

><td class="source">    // this is the setup, based on lx<br></td></tr
><tr
id=sl_svn7768_400

><td class="source">    incrementalizeX(l, r, sp, sdp, lx);<br></td></tr
><tr
id=sl_svn7768_401

><td class="source"><br></td></tr
><tr
id=sl_svn7768_402

><td class="source">    // scan in x, generating pixels<br></td></tr
><tr
id=sl_svn7768_403

><td class="source">    // using parent.width to get actual pixel index<br></td></tr
><tr
id=sl_svn7768_404

><td class="source">    // rather than scaled by smooth factor<br></td></tr
><tr
id=sl_svn7768_405

><td class="source">    int offset = smooth ? parent.width * (y / SUBYRES) : parent.width*y;<br></td></tr
><tr
id=sl_svn7768_406

><td class="source"><br></td></tr
><tr
id=sl_svn7768_407

><td class="source">    int truelx = 0, truerx = 0;<br></td></tr
><tr
id=sl_svn7768_408

><td class="source">    if (smooth) {<br></td></tr
><tr
id=sl_svn7768_409

><td class="source">      truelx = lx / SUBXRES;<br></td></tr
><tr
id=sl_svn7768_410

><td class="source">      truerx = (rx + SUBXRES1) / SUBXRES;<br></td></tr
><tr
id=sl_svn7768_411

><td class="source"><br></td></tr
><tr
id=sl_svn7768_412

><td class="source">      lx = aaleftmin / SUBXRES;<br></td></tr
><tr
id=sl_svn7768_413

><td class="source">      rx = (aarightmax + SUBXRES1) / SUBXRES;<br></td></tr
><tr
id=sl_svn7768_414

><td class="source">      if (lx &lt; 0) lx = 0;<br></td></tr
><tr
id=sl_svn7768_415

><td class="source">      if (rx &gt; parent.width1) rx = parent.width1;<br></td></tr
><tr
id=sl_svn7768_416

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_417

><td class="source"><br></td></tr
><tr
id=sl_svn7768_418

><td class="source">    interpX = false;<br></td></tr
><tr
id=sl_svn7768_419

><td class="source">    int tr, tg, tb, ta;<br></td></tr
><tr
id=sl_svn7768_420

><td class="source"><br></td></tr
><tr
id=sl_svn7768_421

><td class="source">//    System.out.println(&quot;P2D interp uv &quot; + interpUV + &quot; &quot; + <br></td></tr
><tr
id=sl_svn7768_422

><td class="source">//                       vertices[2][U] + &quot; &quot; + vertices[2][V]);<br></td></tr
><tr
id=sl_svn7768_423

><td class="source">    for (int x = lx; x &lt;= rx; x++) {<br></td></tr
><tr
id=sl_svn7768_424

><td class="source">      // map texture based on U, V coords in sp[U] and sp[V]<br></td></tr
><tr
id=sl_svn7768_425

><td class="source">      if (interpUV) {<br></td></tr
><tr
id=sl_svn7768_426

><td class="source">        int tu = (int) (sp[U] * twidth);<br></td></tr
><tr
id=sl_svn7768_427

><td class="source">        int tv = (int) (sp[V] * theight);<br></td></tr
><tr
id=sl_svn7768_428

><td class="source"><br></td></tr
><tr
id=sl_svn7768_429

><td class="source">        if (tu &gt; twidth1) tu = twidth1;<br></td></tr
><tr
id=sl_svn7768_430

><td class="source">        if (tv &gt; theight1) tv = theight1;<br></td></tr
><tr
id=sl_svn7768_431

><td class="source">        if (tu &lt; 0) tu = 0;<br></td></tr
><tr
id=sl_svn7768_432

><td class="source">        if (tv &lt; 0) tv = 0;<br></td></tr
><tr
id=sl_svn7768_433

><td class="source"><br></td></tr
><tr
id=sl_svn7768_434

><td class="source">        int txy = tv*twidth + tu;<br></td></tr
><tr
id=sl_svn7768_435

><td class="source"><br></td></tr
><tr
id=sl_svn7768_436

><td class="source">        int tuf1 = (int) (255f * (sp[U]*twidth - (float)tu));<br></td></tr
><tr
id=sl_svn7768_437

><td class="source">        int tvf1 = (int) (255f * (sp[V]*theight - (float)tv));<br></td></tr
><tr
id=sl_svn7768_438

><td class="source"><br></td></tr
><tr
id=sl_svn7768_439

><td class="source">        // the closer sp[U or V] is to the decimal being zero<br></td></tr
><tr
id=sl_svn7768_440

><td class="source">        // the more coverage it should get of the original pixel<br></td></tr
><tr
id=sl_svn7768_441

><td class="source">        int tuf = 255 - tuf1;<br></td></tr
><tr
id=sl_svn7768_442

><td class="source">        int tvf = 255 - tvf1;<br></td></tr
><tr
id=sl_svn7768_443

><td class="source"><br></td></tr
><tr
id=sl_svn7768_444

><td class="source">        // this code sucks! filled with bugs and slow as hell!<br></td></tr
><tr
id=sl_svn7768_445

><td class="source">        int pixel00 = tpixels[txy];<br></td></tr
><tr
id=sl_svn7768_446

><td class="source">        int pixel01 = (tv &lt; theight1) ?<br></td></tr
><tr
id=sl_svn7768_447

><td class="source">          tpixels[txy + twidth] : tpixels[txy];<br></td></tr
><tr
id=sl_svn7768_448

><td class="source">        int pixel10 = (tu &lt; twidth1) ?<br></td></tr
><tr
id=sl_svn7768_449

><td class="source">          tpixels[txy + 1] : tpixels[txy];<br></td></tr
><tr
id=sl_svn7768_450

><td class="source">        int pixel11 = ((tv &lt; theight1) &amp;&amp; (tu &lt; twidth1)) ?<br></td></tr
><tr
id=sl_svn7768_451

><td class="source">          tpixels[txy + twidth + 1] : tpixels[txy];<br></td></tr
><tr
id=sl_svn7768_452

><td class="source"><br></td></tr
><tr
id=sl_svn7768_453

><td class="source">        int p00, p01, p10, p11;<br></td></tr
><tr
id=sl_svn7768_454

><td class="source">        int px0, px1; //, pxy;<br></td></tr
><tr
id=sl_svn7768_455

><td class="source"><br></td></tr
><tr
id=sl_svn7768_456

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_457

><td class="source">        // calculate alpha component (ta)<br></td></tr
><tr
id=sl_svn7768_458

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_459

><td class="source">        if (tformat == ALPHA) {<br></td></tr
><tr
id=sl_svn7768_460

><td class="source">          px0 = (pixel00*tuf + pixel10*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_461

><td class="source">          px1 = (pixel01*tuf + pixel11*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_462

><td class="source">          ta = (((px0*tvf + px1*tvf1) &gt;&gt; 8) *<br></td></tr
><tr
id=sl_svn7768_463

><td class="source">            (interpARGB ? ((int) (sp[A]*255)) : a2orig)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_464

><td class="source"><br></td></tr
><tr
id=sl_svn7768_465

><td class="source">        } else if (tformat == ARGB) {<br></td></tr
><tr
id=sl_svn7768_466

><td class="source">          p00 = (pixel00 &gt;&gt; 24) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_467

><td class="source">          p01 = (pixel01 &gt;&gt; 24) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_468

><td class="source">          p10 = (pixel10 &gt;&gt; 24) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_469

><td class="source">          p11 = (pixel11 &gt;&gt; 24) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_470

><td class="source"><br></td></tr
><tr
id=sl_svn7768_471

><td class="source">          px0 = (p00*tuf + p10*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_472

><td class="source">          px1 = (p01*tuf + p11*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_473

><td class="source">          ta = (((px0*tvf + px1*tvf1) &gt;&gt; 8) *<br></td></tr
><tr
id=sl_svn7768_474

><td class="source">                (interpARGB ? ((int) (sp[A]*255)) : a2orig)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_475

><td class="source"><br></td></tr
><tr
id=sl_svn7768_476

><td class="source">        } else {  // RGB image, no alpha<br></td></tr
><tr
id=sl_svn7768_477

><td class="source">          ta = interpARGB ? ((int) (sp[A]*255)) : a2orig;<br></td></tr
><tr
id=sl_svn7768_478

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_479

><td class="source"><br></td></tr
><tr
id=sl_svn7768_480

><td class="source">        // calculate r,g,b components (tr, tg, tb)<br></td></tr
><tr
id=sl_svn7768_481

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_482

><td class="source">        if ((tformat == RGB) || (tformat == ARGB)) {<br></td></tr
><tr
id=sl_svn7768_483

><td class="source">          p00 = (pixel00 &gt;&gt; 16) &amp; 0xff;  // red<br></td></tr
><tr
id=sl_svn7768_484

><td class="source">          p01 = (pixel01 &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_485

><td class="source">          p10 = (pixel10 &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_486

><td class="source">          p11 = (pixel11 &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_487

><td class="source"><br></td></tr
><tr
id=sl_svn7768_488

><td class="source">          px0 = (p00*tuf + p10*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_489

><td class="source">          px1 = (p01*tuf + p11*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_490

><td class="source">          tr = (((px0*tvf + px1*tvf1) &gt;&gt; 8) *<br></td></tr
><tr
id=sl_svn7768_491

><td class="source">                (interpARGB ? ((int) (sp[R]*255)) : r2)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_492

><td class="source">                <br></td></tr
><tr
id=sl_svn7768_493

><td class="source">          p00 = (pixel00 &gt;&gt; 8) &amp; 0xff;  // green<br></td></tr
><tr
id=sl_svn7768_494

><td class="source">          p01 = (pixel01 &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_495

><td class="source">          p10 = (pixel10 &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_496

><td class="source">          p11 = (pixel11 &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_497

><td class="source"><br></td></tr
><tr
id=sl_svn7768_498

><td class="source">          px0 = (p00*tuf + p10*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_499

><td class="source">          px1 = (p01*tuf + p11*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_500

><td class="source">          tg = (((px0*tvf + px1*tvf1) &gt;&gt; 8) *<br></td></tr
><tr
id=sl_svn7768_501

><td class="source">                (interpARGB ? ((int) (sp[G]*255)) : g2)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_502

><td class="source"><br></td></tr
><tr
id=sl_svn7768_503

><td class="source">          p00 = pixel00 &amp; 0xff;  // blue<br></td></tr
><tr
id=sl_svn7768_504

><td class="source">          p01 = pixel01 &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_505

><td class="source">          p10 = pixel10 &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_506

><td class="source">          p11 = pixel11 &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_507

><td class="source"><br></td></tr
><tr
id=sl_svn7768_508

><td class="source">          px0 = (p00*tuf + p10*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_509

><td class="source">          px1 = (p01*tuf + p11*tuf1) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_510

><td class="source">          tb = (((px0*tvf + px1*tvf1) &gt;&gt; 8) *<br></td></tr
><tr
id=sl_svn7768_511

><td class="source">                (interpARGB ? ((int) (sp[B]*255)) : b2)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_512

><td class="source"><br></td></tr
><tr
id=sl_svn7768_513

><td class="source">        } else {  // alpha image, only use current fill color<br></td></tr
><tr
id=sl_svn7768_514

><td class="source">          if (interpARGB) {<br></td></tr
><tr
id=sl_svn7768_515

><td class="source">            tr = (int) (sp[R] * 255);<br></td></tr
><tr
id=sl_svn7768_516

><td class="source">            tg = (int) (sp[G] * 255);<br></td></tr
><tr
id=sl_svn7768_517

><td class="source">            tb = (int) (sp[B] * 255);<br></td></tr
><tr
id=sl_svn7768_518

><td class="source"><br></td></tr
><tr
id=sl_svn7768_519

><td class="source">          } else {<br></td></tr
><tr
id=sl_svn7768_520

><td class="source">            tr = r2;<br></td></tr
><tr
id=sl_svn7768_521

><td class="source">            tg = g2;<br></td></tr
><tr
id=sl_svn7768_522

><td class="source">            tb = b2;<br></td></tr
><tr
id=sl_svn7768_523

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_524

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_525

><td class="source"><br></td></tr
><tr
id=sl_svn7768_526

><td class="source">        int weight = smooth ? coverage(x) : 255;<br></td></tr
><tr
id=sl_svn7768_527

><td class="source">        if (weight != 255) ta = ta*weight &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_528

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_529

><td class="source">        if ((ta == 254) || (ta == 255)) {  // if (ta &amp; 0xf8) would be good<br></td></tr
><tr
id=sl_svn7768_530

><td class="source">          // no need to blend<br></td></tr
><tr
id=sl_svn7768_531

><td class="source">          pixels[offset+x] = 0xff000000 | (tr &lt;&lt; 16) | (tg &lt;&lt; 8) | tb;<br></td></tr
><tr
id=sl_svn7768_532

><td class="source"><br></td></tr
><tr
id=sl_svn7768_533

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_534

><td class="source">          // blend with pixel on screen<br></td></tr
><tr
id=sl_svn7768_535

><td class="source">          int a1 = 255-ta;<br></td></tr
><tr
id=sl_svn7768_536

><td class="source">          int r1 = (pixels[offset+x] &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_537

><td class="source">          int g1 = (pixels[offset+x] &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_538

><td class="source">          int b1 = (pixels[offset+x]) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_539

><td class="source"><br></td></tr
><tr
id=sl_svn7768_540

><td class="source">          pixels[offset+x] = 0xff000000 |<br></td></tr
><tr
id=sl_svn7768_541

><td class="source">            (((tr*ta + r1*a1) &gt;&gt; 8) &lt;&lt; 16) |<br></td></tr
><tr
id=sl_svn7768_542

><td class="source">            ((tg*ta + g1*a1) &amp; 0xff00) |<br></td></tr
><tr
id=sl_svn7768_543

><td class="source">            ((tb*ta + b1*a1) &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn7768_544

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_545

><td class="source"><br></td></tr
><tr
id=sl_svn7768_546

><td class="source">      } else {  // no image applied<br></td></tr
><tr
id=sl_svn7768_547

><td class="source">        int weight = smooth ? coverage(x) : 255;<br></td></tr
><tr
id=sl_svn7768_548

><td class="source"><br></td></tr
><tr
id=sl_svn7768_549

><td class="source">        if (interpARGB) {<br></td></tr
><tr
id=sl_svn7768_550

><td class="source">          r2 = (int) (sp[R] * 255);<br></td></tr
><tr
id=sl_svn7768_551

><td class="source">          g2 = (int) (sp[G] * 255);<br></td></tr
><tr
id=sl_svn7768_552

><td class="source">          b2 = (int) (sp[B] * 255);<br></td></tr
><tr
id=sl_svn7768_553

><td class="source">          if (sp[A] != 1) weight = (weight * ((int) (sp[A] * 255))) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_554

><td class="source">          if (weight == 255) {<br></td></tr
><tr
id=sl_svn7768_555

><td class="source">            rgba = 0xff000000 | (r2 &lt;&lt; 16) | (g2 &lt;&lt; 8) | b2;<br></td></tr
><tr
id=sl_svn7768_556

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_557

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_558

><td class="source">          if (a2orig != 255) weight = (weight * a2orig) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_559

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_560

><td class="source"><br></td></tr
><tr
id=sl_svn7768_561

><td class="source">        if (weight == 255) {<br></td></tr
><tr
id=sl_svn7768_562

><td class="source">          // no blend, no aa, just the rgba<br></td></tr
><tr
id=sl_svn7768_563

><td class="source">          pixels[offset+x] = rgba;<br></td></tr
><tr
id=sl_svn7768_564

><td class="source">          //zbuffer[offset+x] = sp[Z];<br></td></tr
><tr
id=sl_svn7768_565

><td class="source"><br></td></tr
><tr
id=sl_svn7768_566

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_567

><td class="source">          int r1 = (pixels[offset+x] &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_568

><td class="source">          int g1 = (pixels[offset+x] &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_569

><td class="source">          int b1 = (pixels[offset+x]) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_570

><td class="source">          a2 = weight;<br></td></tr
><tr
id=sl_svn7768_571

><td class="source"><br></td></tr
><tr
id=sl_svn7768_572

><td class="source">          int a1 = 255 - a2;<br></td></tr
><tr
id=sl_svn7768_573

><td class="source">          pixels[offset+x] = (0xff000000 |<br></td></tr
><tr
id=sl_svn7768_574

><td class="source">                              ((r1*a1 + r2*a2) &gt;&gt; 8) &lt;&lt; 16 |<br></td></tr
><tr
id=sl_svn7768_575

><td class="source">                              // use &amp; instead of &gt;&gt; and &lt;&lt; below<br></td></tr
><tr
id=sl_svn7768_576

><td class="source">                              ((g1*a1 + g2*a2) &gt;&gt; 8) &lt;&lt; 8 |<br></td></tr
><tr
id=sl_svn7768_577

><td class="source">                              ((b1*a1 + b2*a2) &gt;&gt; 8));<br></td></tr
><tr
id=sl_svn7768_578

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_579

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_580

><td class="source"><br></td></tr
><tr
id=sl_svn7768_581

><td class="source">      // if smooth enabled, don&#39;t increment values<br></td></tr
><tr
id=sl_svn7768_582

><td class="source">      // for the pixel in the stretch out version<br></td></tr
><tr
id=sl_svn7768_583

><td class="source">      // of the scanline used to get smooth edges.<br></td></tr
><tr
id=sl_svn7768_584

><td class="source">      if (!smooth || ((x &gt;= truelx) &amp;&amp; (x &lt;= truerx))) {<br></td></tr
><tr
id=sl_svn7768_585

><td class="source">        increment(sp, sdp);<br></td></tr
><tr
id=sl_svn7768_586

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_587

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_588

><td class="source">    firstModY = -1;<br></td></tr
><tr
id=sl_svn7768_589

><td class="source">    interpX = true;<br></td></tr
><tr
id=sl_svn7768_590

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_591

><td class="source"><br></td></tr
><tr
id=sl_svn7768_592

><td class="source"><br></td></tr
><tr
id=sl_svn7768_593

><td class="source">  // x is in screen, not huge 8x coordinates<br></td></tr
><tr
id=sl_svn7768_594

><td class="source">  private int coverage(int x) {<br></td></tr
><tr
id=sl_svn7768_595

><td class="source">    if ((x &gt;= aaleftfull) &amp;&amp; (x &lt;= aarightfull) &amp;&amp;<br></td></tr
><tr
id=sl_svn7768_596

><td class="source">      // important since not all SUBYRES lines may have been covered<br></td></tr
><tr
id=sl_svn7768_597

><td class="source">      (firstModY == 0) &amp;&amp; (lastModY == SUBYRES1)) {<br></td></tr
><tr
id=sl_svn7768_598

><td class="source">      return 255;<br></td></tr
><tr
id=sl_svn7768_599

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_600

><td class="source"><br></td></tr
><tr
id=sl_svn7768_601

><td class="source">    int pixelLeft = x*SUBXRES;  // huh?<br></td></tr
><tr
id=sl_svn7768_602

><td class="source">    int pixelRight = pixelLeft + 8;<br></td></tr
><tr
id=sl_svn7768_603

><td class="source"><br></td></tr
><tr
id=sl_svn7768_604

><td class="source">    int amt = 0;<br></td></tr
><tr
id=sl_svn7768_605

><td class="source">    for (int i = firstModY; i &lt;= lastModY; i++) {<br></td></tr
><tr
id=sl_svn7768_606

><td class="source">      if ((aaleft[i] &gt; pixelRight) || (aaright[i] &lt; pixelLeft)) {<br></td></tr
><tr
id=sl_svn7768_607

><td class="source">        continue;<br></td></tr
><tr
id=sl_svn7768_608

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_609

><td class="source">      // does this need a +1 ?<br></td></tr
><tr
id=sl_svn7768_610

><td class="source">      amt += ((aaright[i] &lt; pixelRight ? aaright[i] : pixelRight) -<br></td></tr
><tr
id=sl_svn7768_611

><td class="source">              (aaleft[i] &gt; pixelLeft ? aaleft[i] : pixelLeft));<br></td></tr
><tr
id=sl_svn7768_612

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_613

><td class="source">    amt &lt;&lt;= 2;<br></td></tr
><tr
id=sl_svn7768_614

><td class="source">    return (amt == 256) ? 255 : amt;<br></td></tr
><tr
id=sl_svn7768_615

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_616

><td class="source"><br></td></tr
><tr
id=sl_svn7768_617

><td class="source"><br></td></tr
><tr
id=sl_svn7768_618

><td class="source">  private void incrementalizeY(float p1[], float p2[],<br></td></tr
><tr
id=sl_svn7768_619

><td class="source">                               float p[], float dp[], int y) {<br></td></tr
><tr
id=sl_svn7768_620

><td class="source">    float delta = p2[TY] - p1[TY];<br></td></tr
><tr
id=sl_svn7768_621

><td class="source">    if (delta == 0) delta = 1;<br></td></tr
><tr
id=sl_svn7768_622

><td class="source">    float fraction = y + 0.5f - p1[TY];<br></td></tr
><tr
id=sl_svn7768_623

><td class="source"><br></td></tr
><tr
id=sl_svn7768_624

><td class="source">    if (interpX) {<br></td></tr
><tr
id=sl_svn7768_625

><td class="source">      dp[TX] = (p2[TX] - p1[TX]) / delta;<br></td></tr
><tr
id=sl_svn7768_626

><td class="source">      p[TX] = p1[TX] + dp[TX] * fraction;<br></td></tr
><tr
id=sl_svn7768_627

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_628

><td class="source"><br></td></tr
><tr
id=sl_svn7768_629

><td class="source">    if (interpARGB) {<br></td></tr
><tr
id=sl_svn7768_630

><td class="source">      dp[R] = (p2[R] - p1[R]) / delta;<br></td></tr
><tr
id=sl_svn7768_631

><td class="source">      dp[G] = (p2[G] - p1[G]) / delta;<br></td></tr
><tr
id=sl_svn7768_632

><td class="source">      dp[B] = (p2[B] - p1[B]) / delta;<br></td></tr
><tr
id=sl_svn7768_633

><td class="source">      dp[A] = (p2[A] - p1[A]) / delta;<br></td></tr
><tr
id=sl_svn7768_634

><td class="source">      p[R] = p1[R] + dp[R] * fraction;<br></td></tr
><tr
id=sl_svn7768_635

><td class="source">      p[G] = p1[G] + dp[G] * fraction;<br></td></tr
><tr
id=sl_svn7768_636

><td class="source">      p[B] = p1[B] + dp[B] * fraction;<br></td></tr
><tr
id=sl_svn7768_637

><td class="source">      p[A] = p1[A] + dp[A] * fraction;<br></td></tr
><tr
id=sl_svn7768_638

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_639

><td class="source"><br></td></tr
><tr
id=sl_svn7768_640

><td class="source">    if (interpUV) {<br></td></tr
><tr
id=sl_svn7768_641

><td class="source">      dp[U] = (p2[U] - p1[U]) / delta;<br></td></tr
><tr
id=sl_svn7768_642

><td class="source">      dp[V] = (p2[V] - p1[V]) / delta;<br></td></tr
><tr
id=sl_svn7768_643

><td class="source"><br></td></tr
><tr
id=sl_svn7768_644

><td class="source">      p[U] = p1[U] + dp[U] * fraction;<br></td></tr
><tr
id=sl_svn7768_645

><td class="source">      p[V] = p1[V] + dp[V] * fraction;<br></td></tr
><tr
id=sl_svn7768_646

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_647

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_648

><td class="source"><br></td></tr
><tr
id=sl_svn7768_649

><td class="source"><br></td></tr
><tr
id=sl_svn7768_650

><td class="source">  private void incrementalizeX(float p1[], float p2[],<br></td></tr
><tr
id=sl_svn7768_651

><td class="source">                               float p[], float dp[], int x) {<br></td></tr
><tr
id=sl_svn7768_652

><td class="source">    float delta = p2[TX] - p1[TX];<br></td></tr
><tr
id=sl_svn7768_653

><td class="source">    if (delta == 0) delta = 1;<br></td></tr
><tr
id=sl_svn7768_654

><td class="source">    float fraction = x + 0.5f - p1[TX];<br></td></tr
><tr
id=sl_svn7768_655

><td class="source">    if (smooth) {<br></td></tr
><tr
id=sl_svn7768_656

><td class="source">      delta /= SUBXRES;<br></td></tr
><tr
id=sl_svn7768_657

><td class="source">      fraction /= SUBXRES;<br></td></tr
><tr
id=sl_svn7768_658

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_659

><td class="source"><br></td></tr
><tr
id=sl_svn7768_660

><td class="source">    if (interpX) {<br></td></tr
><tr
id=sl_svn7768_661

><td class="source">      dp[TX] = (p2[TX] - p1[TX]) / delta;<br></td></tr
><tr
id=sl_svn7768_662

><td class="source">      p[TX] = p1[TX] + dp[TX] * fraction;<br></td></tr
><tr
id=sl_svn7768_663

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_664

><td class="source"><br></td></tr
><tr
id=sl_svn7768_665

><td class="source">    if (interpARGB) {<br></td></tr
><tr
id=sl_svn7768_666

><td class="source">      dp[R] = (p2[R] - p1[R]) / delta;<br></td></tr
><tr
id=sl_svn7768_667

><td class="source">      dp[G] = (p2[G] - p1[G]) / delta;<br></td></tr
><tr
id=sl_svn7768_668

><td class="source">      dp[B] = (p2[B] - p1[B]) / delta;<br></td></tr
><tr
id=sl_svn7768_669

><td class="source">      dp[A] = (p2[A] - p1[A]) / delta;<br></td></tr
><tr
id=sl_svn7768_670

><td class="source">      p[R] = p1[R] + dp[R] * fraction;<br></td></tr
><tr
id=sl_svn7768_671

><td class="source">      p[G] = p1[G] + dp[G] * fraction;<br></td></tr
><tr
id=sl_svn7768_672

><td class="source">      p[B] = p1[B] + dp[B] * fraction;<br></td></tr
><tr
id=sl_svn7768_673

><td class="source">      p[A] = p1[A] + dp[A] * fraction;<br></td></tr
><tr
id=sl_svn7768_674

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_675

><td class="source"><br></td></tr
><tr
id=sl_svn7768_676

><td class="source">    if (interpUV) {<br></td></tr
><tr
id=sl_svn7768_677

><td class="source">      dp[U] = (p2[U] - p1[U]) / delta;<br></td></tr
><tr
id=sl_svn7768_678

><td class="source">      dp[V] = (p2[V] - p1[V]) / delta;<br></td></tr
><tr
id=sl_svn7768_679

><td class="source"><br></td></tr
><tr
id=sl_svn7768_680

><td class="source">      p[U] = p1[U] + dp[U] * fraction;<br></td></tr
><tr
id=sl_svn7768_681

><td class="source">      p[V] = p1[V] + dp[V] * fraction;<br></td></tr
><tr
id=sl_svn7768_682

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_683

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_684

><td class="source"><br></td></tr
><tr
id=sl_svn7768_685

><td class="source"><br></td></tr
><tr
id=sl_svn7768_686

><td class="source">  private void increment(float p[], float dp[]) {<br></td></tr
><tr
id=sl_svn7768_687

><td class="source">    if (interpX) p[TX] += dp[TX];<br></td></tr
><tr
id=sl_svn7768_688

><td class="source"><br></td></tr
><tr
id=sl_svn7768_689

><td class="source">    if (interpARGB) {<br></td></tr
><tr
id=sl_svn7768_690

><td class="source">      p[R] += dp[R];<br></td></tr
><tr
id=sl_svn7768_691

><td class="source">      p[G] += dp[G];<br></td></tr
><tr
id=sl_svn7768_692

><td class="source">      p[B] += dp[B];<br></td></tr
><tr
id=sl_svn7768_693

><td class="source">      p[A] += dp[A];<br></td></tr
><tr
id=sl_svn7768_694

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_695

><td class="source"><br></td></tr
><tr
id=sl_svn7768_696

><td class="source">    if (interpUV) {<br></td></tr
><tr
id=sl_svn7768_697

><td class="source">      p[U] += dp[U];<br></td></tr
><tr
id=sl_svn7768_698

><td class="source">      p[V] += dp[V];<br></td></tr
><tr
id=sl_svn7768_699

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_700

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_701

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
 <a href="/p/processing/source/detail?spec=svn7768&r=5653">r5653</a>
 by fry
 on Jul 31, 2009
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=5653&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old_path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old=5483">Diff</a>
 </div>
 <pre>image() doesn't work with P2D, P3D, and
OPENGL with noFill() (bug #1299)
</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/processing/source/detail?r=5653&spec=svn7768';
 var publish_url = '/p/processing/source/detail?r=5653&spec=svn7768#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PGraphics2D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics2D.java?r\x3d5653\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PGraphics3D.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics3D.java?r\x3d5653\x26spec\x3dsvn7768');
 
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PPolygon.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PPolygon.java?r\x3d5653\x26spec\x3dsvn7768');
 
 var selected_path = '/trunk/processing/core/src/processing/core/PPolygon.java';
 
 
 changed_paths.push('/trunk/processing/core/todo.txt');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/todo.txt?r\x3d5653\x26spec\x3dsvn7768');
 
 
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
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics2D.java?r=5653&amp;spec=svn7768"
 
 >...processing/core/PGraphics2D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PGraphics3D.java?r=5653&amp;spec=svn7768"
 
 >...processing/core/PGraphics3D.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PPolygon.java?r=5653&amp;spec=svn7768"
 selected="selected"
 >...rc/processing/core/PPolygon.java</option>
 
 <option value="/p/processing/source/browse/trunk/processing/core/todo.txt?r=5653&amp;spec=svn7768"
 
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
 <a href="/p/processing/source/detail?spec=svn7768&r=5483">r5483</a>
 by fry
 on Feb 21, 2009
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=5483&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old_path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old=5180">Diff</a>
 <br>
 <pre class="ifOpened">fix problems with tint() in P2D
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=5180">r5180</a>
 by fry
 on Nov 20, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=5180&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old_path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old=5148">Diff</a>
 <br>
 <pre class="ifOpened">improve ellipse/arcImpl with P2D,
separate code from P/P2D/P3D for both,
better adaptive sizing
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=5148">r5148</a>
 by fry
 on Nov 18, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=5148&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old_path=/trunk/processing/core/src/processing/core/PPolygon.java&amp;old=5147">Diff</a>
 <br>
 <pre class="ifOpened">some additional cleanup
</pre>
 </div>
 
 
 <a href="/p/processing/source/list?path=/trunk/processing/core/src/processing/core/PPolygon.java&start=5653">All revisions of this file</a>
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
 
 <div>Size: 20858 bytes,
 701 lines</div>
 
 <div><a href="http://processing.googlecode.com/svn/trunk/processing/core/src/processing/core/PPolygon.java">View raw file</a></div>
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
 var paths = {'svn7768': '/trunk/processing/core/src/processing/core/PPolygon.java'}
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

