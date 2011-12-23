



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 
 
 var codesite_token = "c6974bcd72eb95455827185f7306e1fa";
 
 
 var logged_in_user_email = "Dung.Dang@gmail.com";
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>PTriangle.java - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fprocessing%2Fsource%2Fbrowse%2Ftrunk%2Fprocessing%2Fcore%2Fsrc%2Fprocessing%2Fcore%2FPTriangle.java" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/processing/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/">core</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/">src</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/">processing</a><span class="sp">/&nbsp;</span><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/">core</a><span class="sp">/&nbsp;</span>PTriangle.java</span>
 
 

 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PTriangle.java?edit=1"
 ><img src="http://www.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/processing/source/browse/trunk/processing/core/src/processing/core/PTriangle.java?r=4742" title="Previous">&lsaquo;r4742</a></li>
 
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
><tr id="gr_svn7768_1010"

><td id="1010"><a href="#1010">1010</a></td></tr
><tr id="gr_svn7768_1011"

><td id="1011"><a href="#1011">1011</a></td></tr
><tr id="gr_svn7768_1012"

><td id="1012"><a href="#1012">1012</a></td></tr
><tr id="gr_svn7768_1013"

><td id="1013"><a href="#1013">1013</a></td></tr
><tr id="gr_svn7768_1014"

><td id="1014"><a href="#1014">1014</a></td></tr
><tr id="gr_svn7768_1015"

><td id="1015"><a href="#1015">1015</a></td></tr
><tr id="gr_svn7768_1016"

><td id="1016"><a href="#1016">1016</a></td></tr
><tr id="gr_svn7768_1017"

><td id="1017"><a href="#1017">1017</a></td></tr
><tr id="gr_svn7768_1018"

><td id="1018"><a href="#1018">1018</a></td></tr
><tr id="gr_svn7768_1019"

><td id="1019"><a href="#1019">1019</a></td></tr
><tr id="gr_svn7768_1020"

><td id="1020"><a href="#1020">1020</a></td></tr
><tr id="gr_svn7768_1021"

><td id="1021"><a href="#1021">1021</a></td></tr
><tr id="gr_svn7768_1022"

><td id="1022"><a href="#1022">1022</a></td></tr
><tr id="gr_svn7768_1023"

><td id="1023"><a href="#1023">1023</a></td></tr
><tr id="gr_svn7768_1024"

><td id="1024"><a href="#1024">1024</a></td></tr
><tr id="gr_svn7768_1025"

><td id="1025"><a href="#1025">1025</a></td></tr
><tr id="gr_svn7768_1026"

><td id="1026"><a href="#1026">1026</a></td></tr
><tr id="gr_svn7768_1027"

><td id="1027"><a href="#1027">1027</a></td></tr
><tr id="gr_svn7768_1028"

><td id="1028"><a href="#1028">1028</a></td></tr
><tr id="gr_svn7768_1029"

><td id="1029"><a href="#1029">1029</a></td></tr
><tr id="gr_svn7768_1030"

><td id="1030"><a href="#1030">1030</a></td></tr
><tr id="gr_svn7768_1031"

><td id="1031"><a href="#1031">1031</a></td></tr
><tr id="gr_svn7768_1032"

><td id="1032"><a href="#1032">1032</a></td></tr
><tr id="gr_svn7768_1033"

><td id="1033"><a href="#1033">1033</a></td></tr
><tr id="gr_svn7768_1034"

><td id="1034"><a href="#1034">1034</a></td></tr
><tr id="gr_svn7768_1035"

><td id="1035"><a href="#1035">1035</a></td></tr
><tr id="gr_svn7768_1036"

><td id="1036"><a href="#1036">1036</a></td></tr
><tr id="gr_svn7768_1037"

><td id="1037"><a href="#1037">1037</a></td></tr
><tr id="gr_svn7768_1038"

><td id="1038"><a href="#1038">1038</a></td></tr
><tr id="gr_svn7768_1039"

><td id="1039"><a href="#1039">1039</a></td></tr
><tr id="gr_svn7768_1040"

><td id="1040"><a href="#1040">1040</a></td></tr
><tr id="gr_svn7768_1041"

><td id="1041"><a href="#1041">1041</a></td></tr
><tr id="gr_svn7768_1042"

><td id="1042"><a href="#1042">1042</a></td></tr
><tr id="gr_svn7768_1043"

><td id="1043"><a href="#1043">1043</a></td></tr
><tr id="gr_svn7768_1044"

><td id="1044"><a href="#1044">1044</a></td></tr
><tr id="gr_svn7768_1045"

><td id="1045"><a href="#1045">1045</a></td></tr
><tr id="gr_svn7768_1046"

><td id="1046"><a href="#1046">1046</a></td></tr
><tr id="gr_svn7768_1047"

><td id="1047"><a href="#1047">1047</a></td></tr
><tr id="gr_svn7768_1048"

><td id="1048"><a href="#1048">1048</a></td></tr
><tr id="gr_svn7768_1049"

><td id="1049"><a href="#1049">1049</a></td></tr
><tr id="gr_svn7768_1050"

><td id="1050"><a href="#1050">1050</a></td></tr
><tr id="gr_svn7768_1051"

><td id="1051"><a href="#1051">1051</a></td></tr
><tr id="gr_svn7768_1052"

><td id="1052"><a href="#1052">1052</a></td></tr
><tr id="gr_svn7768_1053"

><td id="1053"><a href="#1053">1053</a></td></tr
><tr id="gr_svn7768_1054"

><td id="1054"><a href="#1054">1054</a></td></tr
><tr id="gr_svn7768_1055"

><td id="1055"><a href="#1055">1055</a></td></tr
><tr id="gr_svn7768_1056"

><td id="1056"><a href="#1056">1056</a></td></tr
><tr id="gr_svn7768_1057"

><td id="1057"><a href="#1057">1057</a></td></tr
><tr id="gr_svn7768_1058"

><td id="1058"><a href="#1058">1058</a></td></tr
><tr id="gr_svn7768_1059"

><td id="1059"><a href="#1059">1059</a></td></tr
><tr id="gr_svn7768_1060"

><td id="1060"><a href="#1060">1060</a></td></tr
><tr id="gr_svn7768_1061"

><td id="1061"><a href="#1061">1061</a></td></tr
><tr id="gr_svn7768_1062"

><td id="1062"><a href="#1062">1062</a></td></tr
><tr id="gr_svn7768_1063"

><td id="1063"><a href="#1063">1063</a></td></tr
><tr id="gr_svn7768_1064"

><td id="1064"><a href="#1064">1064</a></td></tr
><tr id="gr_svn7768_1065"

><td id="1065"><a href="#1065">1065</a></td></tr
><tr id="gr_svn7768_1066"

><td id="1066"><a href="#1066">1066</a></td></tr
><tr id="gr_svn7768_1067"

><td id="1067"><a href="#1067">1067</a></td></tr
><tr id="gr_svn7768_1068"

><td id="1068"><a href="#1068">1068</a></td></tr
><tr id="gr_svn7768_1069"

><td id="1069"><a href="#1069">1069</a></td></tr
><tr id="gr_svn7768_1070"

><td id="1070"><a href="#1070">1070</a></td></tr
><tr id="gr_svn7768_1071"

><td id="1071"><a href="#1071">1071</a></td></tr
><tr id="gr_svn7768_1072"

><td id="1072"><a href="#1072">1072</a></td></tr
><tr id="gr_svn7768_1073"

><td id="1073"><a href="#1073">1073</a></td></tr
><tr id="gr_svn7768_1074"

><td id="1074"><a href="#1074">1074</a></td></tr
><tr id="gr_svn7768_1075"

><td id="1075"><a href="#1075">1075</a></td></tr
><tr id="gr_svn7768_1076"

><td id="1076"><a href="#1076">1076</a></td></tr
><tr id="gr_svn7768_1077"

><td id="1077"><a href="#1077">1077</a></td></tr
><tr id="gr_svn7768_1078"

><td id="1078"><a href="#1078">1078</a></td></tr
><tr id="gr_svn7768_1079"

><td id="1079"><a href="#1079">1079</a></td></tr
><tr id="gr_svn7768_1080"

><td id="1080"><a href="#1080">1080</a></td></tr
><tr id="gr_svn7768_1081"

><td id="1081"><a href="#1081">1081</a></td></tr
><tr id="gr_svn7768_1082"

><td id="1082"><a href="#1082">1082</a></td></tr
><tr id="gr_svn7768_1083"

><td id="1083"><a href="#1083">1083</a></td></tr
><tr id="gr_svn7768_1084"

><td id="1084"><a href="#1084">1084</a></td></tr
><tr id="gr_svn7768_1085"

><td id="1085"><a href="#1085">1085</a></td></tr
><tr id="gr_svn7768_1086"

><td id="1086"><a href="#1086">1086</a></td></tr
><tr id="gr_svn7768_1087"

><td id="1087"><a href="#1087">1087</a></td></tr
><tr id="gr_svn7768_1088"

><td id="1088"><a href="#1088">1088</a></td></tr
><tr id="gr_svn7768_1089"

><td id="1089"><a href="#1089">1089</a></td></tr
><tr id="gr_svn7768_1090"

><td id="1090"><a href="#1090">1090</a></td></tr
><tr id="gr_svn7768_1091"

><td id="1091"><a href="#1091">1091</a></td></tr
><tr id="gr_svn7768_1092"

><td id="1092"><a href="#1092">1092</a></td></tr
><tr id="gr_svn7768_1093"

><td id="1093"><a href="#1093">1093</a></td></tr
><tr id="gr_svn7768_1094"

><td id="1094"><a href="#1094">1094</a></td></tr
><tr id="gr_svn7768_1095"

><td id="1095"><a href="#1095">1095</a></td></tr
><tr id="gr_svn7768_1096"

><td id="1096"><a href="#1096">1096</a></td></tr
><tr id="gr_svn7768_1097"

><td id="1097"><a href="#1097">1097</a></td></tr
><tr id="gr_svn7768_1098"

><td id="1098"><a href="#1098">1098</a></td></tr
><tr id="gr_svn7768_1099"

><td id="1099"><a href="#1099">1099</a></td></tr
><tr id="gr_svn7768_1100"

><td id="1100"><a href="#1100">1100</a></td></tr
><tr id="gr_svn7768_1101"

><td id="1101"><a href="#1101">1101</a></td></tr
><tr id="gr_svn7768_1102"

><td id="1102"><a href="#1102">1102</a></td></tr
><tr id="gr_svn7768_1103"

><td id="1103"><a href="#1103">1103</a></td></tr
><tr id="gr_svn7768_1104"

><td id="1104"><a href="#1104">1104</a></td></tr
><tr id="gr_svn7768_1105"

><td id="1105"><a href="#1105">1105</a></td></tr
><tr id="gr_svn7768_1106"

><td id="1106"><a href="#1106">1106</a></td></tr
><tr id="gr_svn7768_1107"

><td id="1107"><a href="#1107">1107</a></td></tr
><tr id="gr_svn7768_1108"

><td id="1108"><a href="#1108">1108</a></td></tr
><tr id="gr_svn7768_1109"

><td id="1109"><a href="#1109">1109</a></td></tr
><tr id="gr_svn7768_1110"

><td id="1110"><a href="#1110">1110</a></td></tr
><tr id="gr_svn7768_1111"

><td id="1111"><a href="#1111">1111</a></td></tr
><tr id="gr_svn7768_1112"

><td id="1112"><a href="#1112">1112</a></td></tr
><tr id="gr_svn7768_1113"

><td id="1113"><a href="#1113">1113</a></td></tr
><tr id="gr_svn7768_1114"

><td id="1114"><a href="#1114">1114</a></td></tr
><tr id="gr_svn7768_1115"

><td id="1115"><a href="#1115">1115</a></td></tr
><tr id="gr_svn7768_1116"

><td id="1116"><a href="#1116">1116</a></td></tr
><tr id="gr_svn7768_1117"

><td id="1117"><a href="#1117">1117</a></td></tr
><tr id="gr_svn7768_1118"

><td id="1118"><a href="#1118">1118</a></td></tr
><tr id="gr_svn7768_1119"

><td id="1119"><a href="#1119">1119</a></td></tr
><tr id="gr_svn7768_1120"

><td id="1120"><a href="#1120">1120</a></td></tr
><tr id="gr_svn7768_1121"

><td id="1121"><a href="#1121">1121</a></td></tr
><tr id="gr_svn7768_1122"

><td id="1122"><a href="#1122">1122</a></td></tr
><tr id="gr_svn7768_1123"

><td id="1123"><a href="#1123">1123</a></td></tr
><tr id="gr_svn7768_1124"

><td id="1124"><a href="#1124">1124</a></td></tr
><tr id="gr_svn7768_1125"

><td id="1125"><a href="#1125">1125</a></td></tr
><tr id="gr_svn7768_1126"

><td id="1126"><a href="#1126">1126</a></td></tr
><tr id="gr_svn7768_1127"

><td id="1127"><a href="#1127">1127</a></td></tr
><tr id="gr_svn7768_1128"

><td id="1128"><a href="#1128">1128</a></td></tr
><tr id="gr_svn7768_1129"

><td id="1129"><a href="#1129">1129</a></td></tr
><tr id="gr_svn7768_1130"

><td id="1130"><a href="#1130">1130</a></td></tr
><tr id="gr_svn7768_1131"

><td id="1131"><a href="#1131">1131</a></td></tr
><tr id="gr_svn7768_1132"

><td id="1132"><a href="#1132">1132</a></td></tr
><tr id="gr_svn7768_1133"

><td id="1133"><a href="#1133">1133</a></td></tr
><tr id="gr_svn7768_1134"

><td id="1134"><a href="#1134">1134</a></td></tr
><tr id="gr_svn7768_1135"

><td id="1135"><a href="#1135">1135</a></td></tr
><tr id="gr_svn7768_1136"

><td id="1136"><a href="#1136">1136</a></td></tr
><tr id="gr_svn7768_1137"

><td id="1137"><a href="#1137">1137</a></td></tr
><tr id="gr_svn7768_1138"

><td id="1138"><a href="#1138">1138</a></td></tr
><tr id="gr_svn7768_1139"

><td id="1139"><a href="#1139">1139</a></td></tr
><tr id="gr_svn7768_1140"

><td id="1140"><a href="#1140">1140</a></td></tr
><tr id="gr_svn7768_1141"

><td id="1141"><a href="#1141">1141</a></td></tr
><tr id="gr_svn7768_1142"

><td id="1142"><a href="#1142">1142</a></td></tr
><tr id="gr_svn7768_1143"

><td id="1143"><a href="#1143">1143</a></td></tr
><tr id="gr_svn7768_1144"

><td id="1144"><a href="#1144">1144</a></td></tr
><tr id="gr_svn7768_1145"

><td id="1145"><a href="#1145">1145</a></td></tr
><tr id="gr_svn7768_1146"

><td id="1146"><a href="#1146">1146</a></td></tr
><tr id="gr_svn7768_1147"

><td id="1147"><a href="#1147">1147</a></td></tr
><tr id="gr_svn7768_1148"

><td id="1148"><a href="#1148">1148</a></td></tr
><tr id="gr_svn7768_1149"

><td id="1149"><a href="#1149">1149</a></td></tr
><tr id="gr_svn7768_1150"

><td id="1150"><a href="#1150">1150</a></td></tr
><tr id="gr_svn7768_1151"

><td id="1151"><a href="#1151">1151</a></td></tr
><tr id="gr_svn7768_1152"

><td id="1152"><a href="#1152">1152</a></td></tr
><tr id="gr_svn7768_1153"

><td id="1153"><a href="#1153">1153</a></td></tr
><tr id="gr_svn7768_1154"

><td id="1154"><a href="#1154">1154</a></td></tr
><tr id="gr_svn7768_1155"

><td id="1155"><a href="#1155">1155</a></td></tr
><tr id="gr_svn7768_1156"

><td id="1156"><a href="#1156">1156</a></td></tr
><tr id="gr_svn7768_1157"

><td id="1157"><a href="#1157">1157</a></td></tr
><tr id="gr_svn7768_1158"

><td id="1158"><a href="#1158">1158</a></td></tr
><tr id="gr_svn7768_1159"

><td id="1159"><a href="#1159">1159</a></td></tr
><tr id="gr_svn7768_1160"

><td id="1160"><a href="#1160">1160</a></td></tr
><tr id="gr_svn7768_1161"

><td id="1161"><a href="#1161">1161</a></td></tr
><tr id="gr_svn7768_1162"

><td id="1162"><a href="#1162">1162</a></td></tr
><tr id="gr_svn7768_1163"

><td id="1163"><a href="#1163">1163</a></td></tr
><tr id="gr_svn7768_1164"

><td id="1164"><a href="#1164">1164</a></td></tr
><tr id="gr_svn7768_1165"

><td id="1165"><a href="#1165">1165</a></td></tr
><tr id="gr_svn7768_1166"

><td id="1166"><a href="#1166">1166</a></td></tr
><tr id="gr_svn7768_1167"

><td id="1167"><a href="#1167">1167</a></td></tr
><tr id="gr_svn7768_1168"

><td id="1168"><a href="#1168">1168</a></td></tr
><tr id="gr_svn7768_1169"

><td id="1169"><a href="#1169">1169</a></td></tr
><tr id="gr_svn7768_1170"

><td id="1170"><a href="#1170">1170</a></td></tr
><tr id="gr_svn7768_1171"

><td id="1171"><a href="#1171">1171</a></td></tr
><tr id="gr_svn7768_1172"

><td id="1172"><a href="#1172">1172</a></td></tr
><tr id="gr_svn7768_1173"

><td id="1173"><a href="#1173">1173</a></td></tr
><tr id="gr_svn7768_1174"

><td id="1174"><a href="#1174">1174</a></td></tr
><tr id="gr_svn7768_1175"

><td id="1175"><a href="#1175">1175</a></td></tr
><tr id="gr_svn7768_1176"

><td id="1176"><a href="#1176">1176</a></td></tr
><tr id="gr_svn7768_1177"

><td id="1177"><a href="#1177">1177</a></td></tr
><tr id="gr_svn7768_1178"

><td id="1178"><a href="#1178">1178</a></td></tr
><tr id="gr_svn7768_1179"

><td id="1179"><a href="#1179">1179</a></td></tr
><tr id="gr_svn7768_1180"

><td id="1180"><a href="#1180">1180</a></td></tr
><tr id="gr_svn7768_1181"

><td id="1181"><a href="#1181">1181</a></td></tr
><tr id="gr_svn7768_1182"

><td id="1182"><a href="#1182">1182</a></td></tr
><tr id="gr_svn7768_1183"

><td id="1183"><a href="#1183">1183</a></td></tr
><tr id="gr_svn7768_1184"

><td id="1184"><a href="#1184">1184</a></td></tr
><tr id="gr_svn7768_1185"

><td id="1185"><a href="#1185">1185</a></td></tr
><tr id="gr_svn7768_1186"

><td id="1186"><a href="#1186">1186</a></td></tr
><tr id="gr_svn7768_1187"

><td id="1187"><a href="#1187">1187</a></td></tr
><tr id="gr_svn7768_1188"

><td id="1188"><a href="#1188">1188</a></td></tr
><tr id="gr_svn7768_1189"

><td id="1189"><a href="#1189">1189</a></td></tr
><tr id="gr_svn7768_1190"

><td id="1190"><a href="#1190">1190</a></td></tr
><tr id="gr_svn7768_1191"

><td id="1191"><a href="#1191">1191</a></td></tr
><tr id="gr_svn7768_1192"

><td id="1192"><a href="#1192">1192</a></td></tr
><tr id="gr_svn7768_1193"

><td id="1193"><a href="#1193">1193</a></td></tr
><tr id="gr_svn7768_1194"

><td id="1194"><a href="#1194">1194</a></td></tr
><tr id="gr_svn7768_1195"

><td id="1195"><a href="#1195">1195</a></td></tr
><tr id="gr_svn7768_1196"

><td id="1196"><a href="#1196">1196</a></td></tr
><tr id="gr_svn7768_1197"

><td id="1197"><a href="#1197">1197</a></td></tr
><tr id="gr_svn7768_1198"

><td id="1198"><a href="#1198">1198</a></td></tr
><tr id="gr_svn7768_1199"

><td id="1199"><a href="#1199">1199</a></td></tr
><tr id="gr_svn7768_1200"

><td id="1200"><a href="#1200">1200</a></td></tr
><tr id="gr_svn7768_1201"

><td id="1201"><a href="#1201">1201</a></td></tr
><tr id="gr_svn7768_1202"

><td id="1202"><a href="#1202">1202</a></td></tr
><tr id="gr_svn7768_1203"

><td id="1203"><a href="#1203">1203</a></td></tr
><tr id="gr_svn7768_1204"

><td id="1204"><a href="#1204">1204</a></td></tr
><tr id="gr_svn7768_1205"

><td id="1205"><a href="#1205">1205</a></td></tr
><tr id="gr_svn7768_1206"

><td id="1206"><a href="#1206">1206</a></td></tr
><tr id="gr_svn7768_1207"

><td id="1207"><a href="#1207">1207</a></td></tr
><tr id="gr_svn7768_1208"

><td id="1208"><a href="#1208">1208</a></td></tr
><tr id="gr_svn7768_1209"

><td id="1209"><a href="#1209">1209</a></td></tr
><tr id="gr_svn7768_1210"

><td id="1210"><a href="#1210">1210</a></td></tr
><tr id="gr_svn7768_1211"

><td id="1211"><a href="#1211">1211</a></td></tr
><tr id="gr_svn7768_1212"

><td id="1212"><a href="#1212">1212</a></td></tr
><tr id="gr_svn7768_1213"

><td id="1213"><a href="#1213">1213</a></td></tr
><tr id="gr_svn7768_1214"

><td id="1214"><a href="#1214">1214</a></td></tr
><tr id="gr_svn7768_1215"

><td id="1215"><a href="#1215">1215</a></td></tr
><tr id="gr_svn7768_1216"

><td id="1216"><a href="#1216">1216</a></td></tr
><tr id="gr_svn7768_1217"

><td id="1217"><a href="#1217">1217</a></td></tr
><tr id="gr_svn7768_1218"

><td id="1218"><a href="#1218">1218</a></td></tr
><tr id="gr_svn7768_1219"

><td id="1219"><a href="#1219">1219</a></td></tr
><tr id="gr_svn7768_1220"

><td id="1220"><a href="#1220">1220</a></td></tr
><tr id="gr_svn7768_1221"

><td id="1221"><a href="#1221">1221</a></td></tr
><tr id="gr_svn7768_1222"

><td id="1222"><a href="#1222">1222</a></td></tr
><tr id="gr_svn7768_1223"

><td id="1223"><a href="#1223">1223</a></td></tr
><tr id="gr_svn7768_1224"

><td id="1224"><a href="#1224">1224</a></td></tr
><tr id="gr_svn7768_1225"

><td id="1225"><a href="#1225">1225</a></td></tr
><tr id="gr_svn7768_1226"

><td id="1226"><a href="#1226">1226</a></td></tr
><tr id="gr_svn7768_1227"

><td id="1227"><a href="#1227">1227</a></td></tr
><tr id="gr_svn7768_1228"

><td id="1228"><a href="#1228">1228</a></td></tr
><tr id="gr_svn7768_1229"

><td id="1229"><a href="#1229">1229</a></td></tr
><tr id="gr_svn7768_1230"

><td id="1230"><a href="#1230">1230</a></td></tr
><tr id="gr_svn7768_1231"

><td id="1231"><a href="#1231">1231</a></td></tr
><tr id="gr_svn7768_1232"

><td id="1232"><a href="#1232">1232</a></td></tr
><tr id="gr_svn7768_1233"

><td id="1233"><a href="#1233">1233</a></td></tr
><tr id="gr_svn7768_1234"

><td id="1234"><a href="#1234">1234</a></td></tr
><tr id="gr_svn7768_1235"

><td id="1235"><a href="#1235">1235</a></td></tr
><tr id="gr_svn7768_1236"

><td id="1236"><a href="#1236">1236</a></td></tr
><tr id="gr_svn7768_1237"

><td id="1237"><a href="#1237">1237</a></td></tr
><tr id="gr_svn7768_1238"

><td id="1238"><a href="#1238">1238</a></td></tr
><tr id="gr_svn7768_1239"

><td id="1239"><a href="#1239">1239</a></td></tr
><tr id="gr_svn7768_1240"

><td id="1240"><a href="#1240">1240</a></td></tr
><tr id="gr_svn7768_1241"

><td id="1241"><a href="#1241">1241</a></td></tr
><tr id="gr_svn7768_1242"

><td id="1242"><a href="#1242">1242</a></td></tr
><tr id="gr_svn7768_1243"

><td id="1243"><a href="#1243">1243</a></td></tr
><tr id="gr_svn7768_1244"

><td id="1244"><a href="#1244">1244</a></td></tr
><tr id="gr_svn7768_1245"

><td id="1245"><a href="#1245">1245</a></td></tr
><tr id="gr_svn7768_1246"

><td id="1246"><a href="#1246">1246</a></td></tr
><tr id="gr_svn7768_1247"

><td id="1247"><a href="#1247">1247</a></td></tr
><tr id="gr_svn7768_1248"

><td id="1248"><a href="#1248">1248</a></td></tr
><tr id="gr_svn7768_1249"

><td id="1249"><a href="#1249">1249</a></td></tr
><tr id="gr_svn7768_1250"

><td id="1250"><a href="#1250">1250</a></td></tr
><tr id="gr_svn7768_1251"

><td id="1251"><a href="#1251">1251</a></td></tr
><tr id="gr_svn7768_1252"

><td id="1252"><a href="#1252">1252</a></td></tr
><tr id="gr_svn7768_1253"

><td id="1253"><a href="#1253">1253</a></td></tr
><tr id="gr_svn7768_1254"

><td id="1254"><a href="#1254">1254</a></td></tr
><tr id="gr_svn7768_1255"

><td id="1255"><a href="#1255">1255</a></td></tr
><tr id="gr_svn7768_1256"

><td id="1256"><a href="#1256">1256</a></td></tr
><tr id="gr_svn7768_1257"

><td id="1257"><a href="#1257">1257</a></td></tr
><tr id="gr_svn7768_1258"

><td id="1258"><a href="#1258">1258</a></td></tr
><tr id="gr_svn7768_1259"

><td id="1259"><a href="#1259">1259</a></td></tr
><tr id="gr_svn7768_1260"

><td id="1260"><a href="#1260">1260</a></td></tr
><tr id="gr_svn7768_1261"

><td id="1261"><a href="#1261">1261</a></td></tr
><tr id="gr_svn7768_1262"

><td id="1262"><a href="#1262">1262</a></td></tr
><tr id="gr_svn7768_1263"

><td id="1263"><a href="#1263">1263</a></td></tr
><tr id="gr_svn7768_1264"

><td id="1264"><a href="#1264">1264</a></td></tr
><tr id="gr_svn7768_1265"

><td id="1265"><a href="#1265">1265</a></td></tr
><tr id="gr_svn7768_1266"

><td id="1266"><a href="#1266">1266</a></td></tr
><tr id="gr_svn7768_1267"

><td id="1267"><a href="#1267">1267</a></td></tr
><tr id="gr_svn7768_1268"

><td id="1268"><a href="#1268">1268</a></td></tr
><tr id="gr_svn7768_1269"

><td id="1269"><a href="#1269">1269</a></td></tr
><tr id="gr_svn7768_1270"

><td id="1270"><a href="#1270">1270</a></td></tr
><tr id="gr_svn7768_1271"

><td id="1271"><a href="#1271">1271</a></td></tr
><tr id="gr_svn7768_1272"

><td id="1272"><a href="#1272">1272</a></td></tr
><tr id="gr_svn7768_1273"

><td id="1273"><a href="#1273">1273</a></td></tr
><tr id="gr_svn7768_1274"

><td id="1274"><a href="#1274">1274</a></td></tr
><tr id="gr_svn7768_1275"

><td id="1275"><a href="#1275">1275</a></td></tr
><tr id="gr_svn7768_1276"

><td id="1276"><a href="#1276">1276</a></td></tr
><tr id="gr_svn7768_1277"

><td id="1277"><a href="#1277">1277</a></td></tr
><tr id="gr_svn7768_1278"

><td id="1278"><a href="#1278">1278</a></td></tr
><tr id="gr_svn7768_1279"

><td id="1279"><a href="#1279">1279</a></td></tr
><tr id="gr_svn7768_1280"

><td id="1280"><a href="#1280">1280</a></td></tr
><tr id="gr_svn7768_1281"

><td id="1281"><a href="#1281">1281</a></td></tr
><tr id="gr_svn7768_1282"

><td id="1282"><a href="#1282">1282</a></td></tr
><tr id="gr_svn7768_1283"

><td id="1283"><a href="#1283">1283</a></td></tr
><tr id="gr_svn7768_1284"

><td id="1284"><a href="#1284">1284</a></td></tr
><tr id="gr_svn7768_1285"

><td id="1285"><a href="#1285">1285</a></td></tr
><tr id="gr_svn7768_1286"

><td id="1286"><a href="#1286">1286</a></td></tr
><tr id="gr_svn7768_1287"

><td id="1287"><a href="#1287">1287</a></td></tr
><tr id="gr_svn7768_1288"

><td id="1288"><a href="#1288">1288</a></td></tr
><tr id="gr_svn7768_1289"

><td id="1289"><a href="#1289">1289</a></td></tr
><tr id="gr_svn7768_1290"

><td id="1290"><a href="#1290">1290</a></td></tr
><tr id="gr_svn7768_1291"

><td id="1291"><a href="#1291">1291</a></td></tr
><tr id="gr_svn7768_1292"

><td id="1292"><a href="#1292">1292</a></td></tr
><tr id="gr_svn7768_1293"

><td id="1293"><a href="#1293">1293</a></td></tr
><tr id="gr_svn7768_1294"

><td id="1294"><a href="#1294">1294</a></td></tr
><tr id="gr_svn7768_1295"

><td id="1295"><a href="#1295">1295</a></td></tr
><tr id="gr_svn7768_1296"

><td id="1296"><a href="#1296">1296</a></td></tr
><tr id="gr_svn7768_1297"

><td id="1297"><a href="#1297">1297</a></td></tr
><tr id="gr_svn7768_1298"

><td id="1298"><a href="#1298">1298</a></td></tr
><tr id="gr_svn7768_1299"

><td id="1299"><a href="#1299">1299</a></td></tr
><tr id="gr_svn7768_1300"

><td id="1300"><a href="#1300">1300</a></td></tr
><tr id="gr_svn7768_1301"

><td id="1301"><a href="#1301">1301</a></td></tr
><tr id="gr_svn7768_1302"

><td id="1302"><a href="#1302">1302</a></td></tr
><tr id="gr_svn7768_1303"

><td id="1303"><a href="#1303">1303</a></td></tr
><tr id="gr_svn7768_1304"

><td id="1304"><a href="#1304">1304</a></td></tr
><tr id="gr_svn7768_1305"

><td id="1305"><a href="#1305">1305</a></td></tr
><tr id="gr_svn7768_1306"

><td id="1306"><a href="#1306">1306</a></td></tr
><tr id="gr_svn7768_1307"

><td id="1307"><a href="#1307">1307</a></td></tr
><tr id="gr_svn7768_1308"

><td id="1308"><a href="#1308">1308</a></td></tr
><tr id="gr_svn7768_1309"

><td id="1309"><a href="#1309">1309</a></td></tr
><tr id="gr_svn7768_1310"

><td id="1310"><a href="#1310">1310</a></td></tr
><tr id="gr_svn7768_1311"

><td id="1311"><a href="#1311">1311</a></td></tr
><tr id="gr_svn7768_1312"

><td id="1312"><a href="#1312">1312</a></td></tr
><tr id="gr_svn7768_1313"

><td id="1313"><a href="#1313">1313</a></td></tr
><tr id="gr_svn7768_1314"

><td id="1314"><a href="#1314">1314</a></td></tr
><tr id="gr_svn7768_1315"

><td id="1315"><a href="#1315">1315</a></td></tr
><tr id="gr_svn7768_1316"

><td id="1316"><a href="#1316">1316</a></td></tr
><tr id="gr_svn7768_1317"

><td id="1317"><a href="#1317">1317</a></td></tr
><tr id="gr_svn7768_1318"

><td id="1318"><a href="#1318">1318</a></td></tr
><tr id="gr_svn7768_1319"

><td id="1319"><a href="#1319">1319</a></td></tr
><tr id="gr_svn7768_1320"

><td id="1320"><a href="#1320">1320</a></td></tr
><tr id="gr_svn7768_1321"

><td id="1321"><a href="#1321">1321</a></td></tr
><tr id="gr_svn7768_1322"

><td id="1322"><a href="#1322">1322</a></td></tr
><tr id="gr_svn7768_1323"

><td id="1323"><a href="#1323">1323</a></td></tr
><tr id="gr_svn7768_1324"

><td id="1324"><a href="#1324">1324</a></td></tr
><tr id="gr_svn7768_1325"

><td id="1325"><a href="#1325">1325</a></td></tr
><tr id="gr_svn7768_1326"

><td id="1326"><a href="#1326">1326</a></td></tr
><tr id="gr_svn7768_1327"

><td id="1327"><a href="#1327">1327</a></td></tr
><tr id="gr_svn7768_1328"

><td id="1328"><a href="#1328">1328</a></td></tr
><tr id="gr_svn7768_1329"

><td id="1329"><a href="#1329">1329</a></td></tr
><tr id="gr_svn7768_1330"

><td id="1330"><a href="#1330">1330</a></td></tr
><tr id="gr_svn7768_1331"

><td id="1331"><a href="#1331">1331</a></td></tr
><tr id="gr_svn7768_1332"

><td id="1332"><a href="#1332">1332</a></td></tr
><tr id="gr_svn7768_1333"

><td id="1333"><a href="#1333">1333</a></td></tr
><tr id="gr_svn7768_1334"

><td id="1334"><a href="#1334">1334</a></td></tr
><tr id="gr_svn7768_1335"

><td id="1335"><a href="#1335">1335</a></td></tr
><tr id="gr_svn7768_1336"

><td id="1336"><a href="#1336">1336</a></td></tr
><tr id="gr_svn7768_1337"

><td id="1337"><a href="#1337">1337</a></td></tr
><tr id="gr_svn7768_1338"

><td id="1338"><a href="#1338">1338</a></td></tr
><tr id="gr_svn7768_1339"

><td id="1339"><a href="#1339">1339</a></td></tr
><tr id="gr_svn7768_1340"

><td id="1340"><a href="#1340">1340</a></td></tr
><tr id="gr_svn7768_1341"

><td id="1341"><a href="#1341">1341</a></td></tr
><tr id="gr_svn7768_1342"

><td id="1342"><a href="#1342">1342</a></td></tr
><tr id="gr_svn7768_1343"

><td id="1343"><a href="#1343">1343</a></td></tr
><tr id="gr_svn7768_1344"

><td id="1344"><a href="#1344">1344</a></td></tr
><tr id="gr_svn7768_1345"

><td id="1345"><a href="#1345">1345</a></td></tr
><tr id="gr_svn7768_1346"

><td id="1346"><a href="#1346">1346</a></td></tr
><tr id="gr_svn7768_1347"

><td id="1347"><a href="#1347">1347</a></td></tr
><tr id="gr_svn7768_1348"

><td id="1348"><a href="#1348">1348</a></td></tr
><tr id="gr_svn7768_1349"

><td id="1349"><a href="#1349">1349</a></td></tr
><tr id="gr_svn7768_1350"

><td id="1350"><a href="#1350">1350</a></td></tr
><tr id="gr_svn7768_1351"

><td id="1351"><a href="#1351">1351</a></td></tr
><tr id="gr_svn7768_1352"

><td id="1352"><a href="#1352">1352</a></td></tr
><tr id="gr_svn7768_1353"

><td id="1353"><a href="#1353">1353</a></td></tr
><tr id="gr_svn7768_1354"

><td id="1354"><a href="#1354">1354</a></td></tr
><tr id="gr_svn7768_1355"

><td id="1355"><a href="#1355">1355</a></td></tr
><tr id="gr_svn7768_1356"

><td id="1356"><a href="#1356">1356</a></td></tr
><tr id="gr_svn7768_1357"

><td id="1357"><a href="#1357">1357</a></td></tr
><tr id="gr_svn7768_1358"

><td id="1358"><a href="#1358">1358</a></td></tr
><tr id="gr_svn7768_1359"

><td id="1359"><a href="#1359">1359</a></td></tr
><tr id="gr_svn7768_1360"

><td id="1360"><a href="#1360">1360</a></td></tr
><tr id="gr_svn7768_1361"

><td id="1361"><a href="#1361">1361</a></td></tr
><tr id="gr_svn7768_1362"

><td id="1362"><a href="#1362">1362</a></td></tr
><tr id="gr_svn7768_1363"

><td id="1363"><a href="#1363">1363</a></td></tr
><tr id="gr_svn7768_1364"

><td id="1364"><a href="#1364">1364</a></td></tr
><tr id="gr_svn7768_1365"

><td id="1365"><a href="#1365">1365</a></td></tr
><tr id="gr_svn7768_1366"

><td id="1366"><a href="#1366">1366</a></td></tr
><tr id="gr_svn7768_1367"

><td id="1367"><a href="#1367">1367</a></td></tr
><tr id="gr_svn7768_1368"

><td id="1368"><a href="#1368">1368</a></td></tr
><tr id="gr_svn7768_1369"

><td id="1369"><a href="#1369">1369</a></td></tr
><tr id="gr_svn7768_1370"

><td id="1370"><a href="#1370">1370</a></td></tr
><tr id="gr_svn7768_1371"

><td id="1371"><a href="#1371">1371</a></td></tr
><tr id="gr_svn7768_1372"

><td id="1372"><a href="#1372">1372</a></td></tr
><tr id="gr_svn7768_1373"

><td id="1373"><a href="#1373">1373</a></td></tr
><tr id="gr_svn7768_1374"

><td id="1374"><a href="#1374">1374</a></td></tr
><tr id="gr_svn7768_1375"

><td id="1375"><a href="#1375">1375</a></td></tr
><tr id="gr_svn7768_1376"

><td id="1376"><a href="#1376">1376</a></td></tr
><tr id="gr_svn7768_1377"

><td id="1377"><a href="#1377">1377</a></td></tr
><tr id="gr_svn7768_1378"

><td id="1378"><a href="#1378">1378</a></td></tr
><tr id="gr_svn7768_1379"

><td id="1379"><a href="#1379">1379</a></td></tr
><tr id="gr_svn7768_1380"

><td id="1380"><a href="#1380">1380</a></td></tr
><tr id="gr_svn7768_1381"

><td id="1381"><a href="#1381">1381</a></td></tr
><tr id="gr_svn7768_1382"

><td id="1382"><a href="#1382">1382</a></td></tr
><tr id="gr_svn7768_1383"

><td id="1383"><a href="#1383">1383</a></td></tr
><tr id="gr_svn7768_1384"

><td id="1384"><a href="#1384">1384</a></td></tr
><tr id="gr_svn7768_1385"

><td id="1385"><a href="#1385">1385</a></td></tr
><tr id="gr_svn7768_1386"

><td id="1386"><a href="#1386">1386</a></td></tr
><tr id="gr_svn7768_1387"

><td id="1387"><a href="#1387">1387</a></td></tr
><tr id="gr_svn7768_1388"

><td id="1388"><a href="#1388">1388</a></td></tr
><tr id="gr_svn7768_1389"

><td id="1389"><a href="#1389">1389</a></td></tr
><tr id="gr_svn7768_1390"

><td id="1390"><a href="#1390">1390</a></td></tr
><tr id="gr_svn7768_1391"

><td id="1391"><a href="#1391">1391</a></td></tr
><tr id="gr_svn7768_1392"

><td id="1392"><a href="#1392">1392</a></td></tr
><tr id="gr_svn7768_1393"

><td id="1393"><a href="#1393">1393</a></td></tr
><tr id="gr_svn7768_1394"

><td id="1394"><a href="#1394">1394</a></td></tr
><tr id="gr_svn7768_1395"

><td id="1395"><a href="#1395">1395</a></td></tr
><tr id="gr_svn7768_1396"

><td id="1396"><a href="#1396">1396</a></td></tr
><tr id="gr_svn7768_1397"

><td id="1397"><a href="#1397">1397</a></td></tr
><tr id="gr_svn7768_1398"

><td id="1398"><a href="#1398">1398</a></td></tr
><tr id="gr_svn7768_1399"

><td id="1399"><a href="#1399">1399</a></td></tr
><tr id="gr_svn7768_1400"

><td id="1400"><a href="#1400">1400</a></td></tr
><tr id="gr_svn7768_1401"

><td id="1401"><a href="#1401">1401</a></td></tr
><tr id="gr_svn7768_1402"

><td id="1402"><a href="#1402">1402</a></td></tr
><tr id="gr_svn7768_1403"

><td id="1403"><a href="#1403">1403</a></td></tr
><tr id="gr_svn7768_1404"

><td id="1404"><a href="#1404">1404</a></td></tr
><tr id="gr_svn7768_1405"

><td id="1405"><a href="#1405">1405</a></td></tr
><tr id="gr_svn7768_1406"

><td id="1406"><a href="#1406">1406</a></td></tr
><tr id="gr_svn7768_1407"

><td id="1407"><a href="#1407">1407</a></td></tr
><tr id="gr_svn7768_1408"

><td id="1408"><a href="#1408">1408</a></td></tr
><tr id="gr_svn7768_1409"

><td id="1409"><a href="#1409">1409</a></td></tr
><tr id="gr_svn7768_1410"

><td id="1410"><a href="#1410">1410</a></td></tr
><tr id="gr_svn7768_1411"

><td id="1411"><a href="#1411">1411</a></td></tr
><tr id="gr_svn7768_1412"

><td id="1412"><a href="#1412">1412</a></td></tr
><tr id="gr_svn7768_1413"

><td id="1413"><a href="#1413">1413</a></td></tr
><tr id="gr_svn7768_1414"

><td id="1414"><a href="#1414">1414</a></td></tr
><tr id="gr_svn7768_1415"

><td id="1415"><a href="#1415">1415</a></td></tr
><tr id="gr_svn7768_1416"

><td id="1416"><a href="#1416">1416</a></td></tr
><tr id="gr_svn7768_1417"

><td id="1417"><a href="#1417">1417</a></td></tr
><tr id="gr_svn7768_1418"

><td id="1418"><a href="#1418">1418</a></td></tr
><tr id="gr_svn7768_1419"

><td id="1419"><a href="#1419">1419</a></td></tr
><tr id="gr_svn7768_1420"

><td id="1420"><a href="#1420">1420</a></td></tr
><tr id="gr_svn7768_1421"

><td id="1421"><a href="#1421">1421</a></td></tr
><tr id="gr_svn7768_1422"

><td id="1422"><a href="#1422">1422</a></td></tr
><tr id="gr_svn7768_1423"

><td id="1423"><a href="#1423">1423</a></td></tr
><tr id="gr_svn7768_1424"

><td id="1424"><a href="#1424">1424</a></td></tr
><tr id="gr_svn7768_1425"

><td id="1425"><a href="#1425">1425</a></td></tr
><tr id="gr_svn7768_1426"

><td id="1426"><a href="#1426">1426</a></td></tr
><tr id="gr_svn7768_1427"

><td id="1427"><a href="#1427">1427</a></td></tr
><tr id="gr_svn7768_1428"

><td id="1428"><a href="#1428">1428</a></td></tr
><tr id="gr_svn7768_1429"

><td id="1429"><a href="#1429">1429</a></td></tr
><tr id="gr_svn7768_1430"

><td id="1430"><a href="#1430">1430</a></td></tr
><tr id="gr_svn7768_1431"

><td id="1431"><a href="#1431">1431</a></td></tr
><tr id="gr_svn7768_1432"

><td id="1432"><a href="#1432">1432</a></td></tr
><tr id="gr_svn7768_1433"

><td id="1433"><a href="#1433">1433</a></td></tr
><tr id="gr_svn7768_1434"

><td id="1434"><a href="#1434">1434</a></td></tr
><tr id="gr_svn7768_1435"

><td id="1435"><a href="#1435">1435</a></td></tr
><tr id="gr_svn7768_1436"

><td id="1436"><a href="#1436">1436</a></td></tr
><tr id="gr_svn7768_1437"

><td id="1437"><a href="#1437">1437</a></td></tr
><tr id="gr_svn7768_1438"

><td id="1438"><a href="#1438">1438</a></td></tr
><tr id="gr_svn7768_1439"

><td id="1439"><a href="#1439">1439</a></td></tr
><tr id="gr_svn7768_1440"

><td id="1440"><a href="#1440">1440</a></td></tr
><tr id="gr_svn7768_1441"

><td id="1441"><a href="#1441">1441</a></td></tr
><tr id="gr_svn7768_1442"

><td id="1442"><a href="#1442">1442</a></td></tr
><tr id="gr_svn7768_1443"

><td id="1443"><a href="#1443">1443</a></td></tr
><tr id="gr_svn7768_1444"

><td id="1444"><a href="#1444">1444</a></td></tr
><tr id="gr_svn7768_1445"

><td id="1445"><a href="#1445">1445</a></td></tr
><tr id="gr_svn7768_1446"

><td id="1446"><a href="#1446">1446</a></td></tr
><tr id="gr_svn7768_1447"

><td id="1447"><a href="#1447">1447</a></td></tr
><tr id="gr_svn7768_1448"

><td id="1448"><a href="#1448">1448</a></td></tr
><tr id="gr_svn7768_1449"

><td id="1449"><a href="#1449">1449</a></td></tr
><tr id="gr_svn7768_1450"

><td id="1450"><a href="#1450">1450</a></td></tr
><tr id="gr_svn7768_1451"

><td id="1451"><a href="#1451">1451</a></td></tr
><tr id="gr_svn7768_1452"

><td id="1452"><a href="#1452">1452</a></td></tr
><tr id="gr_svn7768_1453"

><td id="1453"><a href="#1453">1453</a></td></tr
><tr id="gr_svn7768_1454"

><td id="1454"><a href="#1454">1454</a></td></tr
><tr id="gr_svn7768_1455"

><td id="1455"><a href="#1455">1455</a></td></tr
><tr id="gr_svn7768_1456"

><td id="1456"><a href="#1456">1456</a></td></tr
><tr id="gr_svn7768_1457"

><td id="1457"><a href="#1457">1457</a></td></tr
><tr id="gr_svn7768_1458"

><td id="1458"><a href="#1458">1458</a></td></tr
><tr id="gr_svn7768_1459"

><td id="1459"><a href="#1459">1459</a></td></tr
><tr id="gr_svn7768_1460"

><td id="1460"><a href="#1460">1460</a></td></tr
><tr id="gr_svn7768_1461"

><td id="1461"><a href="#1461">1461</a></td></tr
><tr id="gr_svn7768_1462"

><td id="1462"><a href="#1462">1462</a></td></tr
><tr id="gr_svn7768_1463"

><td id="1463"><a href="#1463">1463</a></td></tr
><tr id="gr_svn7768_1464"

><td id="1464"><a href="#1464">1464</a></td></tr
><tr id="gr_svn7768_1465"

><td id="1465"><a href="#1465">1465</a></td></tr
><tr id="gr_svn7768_1466"

><td id="1466"><a href="#1466">1466</a></td></tr
><tr id="gr_svn7768_1467"

><td id="1467"><a href="#1467">1467</a></td></tr
><tr id="gr_svn7768_1468"

><td id="1468"><a href="#1468">1468</a></td></tr
><tr id="gr_svn7768_1469"

><td id="1469"><a href="#1469">1469</a></td></tr
><tr id="gr_svn7768_1470"

><td id="1470"><a href="#1470">1470</a></td></tr
><tr id="gr_svn7768_1471"

><td id="1471"><a href="#1471">1471</a></td></tr
><tr id="gr_svn7768_1472"

><td id="1472"><a href="#1472">1472</a></td></tr
><tr id="gr_svn7768_1473"

><td id="1473"><a href="#1473">1473</a></td></tr
><tr id="gr_svn7768_1474"

><td id="1474"><a href="#1474">1474</a></td></tr
><tr id="gr_svn7768_1475"

><td id="1475"><a href="#1475">1475</a></td></tr
><tr id="gr_svn7768_1476"

><td id="1476"><a href="#1476">1476</a></td></tr
><tr id="gr_svn7768_1477"

><td id="1477"><a href="#1477">1477</a></td></tr
><tr id="gr_svn7768_1478"

><td id="1478"><a href="#1478">1478</a></td></tr
><tr id="gr_svn7768_1479"

><td id="1479"><a href="#1479">1479</a></td></tr
><tr id="gr_svn7768_1480"

><td id="1480"><a href="#1480">1480</a></td></tr
><tr id="gr_svn7768_1481"

><td id="1481"><a href="#1481">1481</a></td></tr
><tr id="gr_svn7768_1482"

><td id="1482"><a href="#1482">1482</a></td></tr
><tr id="gr_svn7768_1483"

><td id="1483"><a href="#1483">1483</a></td></tr
><tr id="gr_svn7768_1484"

><td id="1484"><a href="#1484">1484</a></td></tr
><tr id="gr_svn7768_1485"

><td id="1485"><a href="#1485">1485</a></td></tr
><tr id="gr_svn7768_1486"

><td id="1486"><a href="#1486">1486</a></td></tr
><tr id="gr_svn7768_1487"

><td id="1487"><a href="#1487">1487</a></td></tr
><tr id="gr_svn7768_1488"

><td id="1488"><a href="#1488">1488</a></td></tr
><tr id="gr_svn7768_1489"

><td id="1489"><a href="#1489">1489</a></td></tr
><tr id="gr_svn7768_1490"

><td id="1490"><a href="#1490">1490</a></td></tr
><tr id="gr_svn7768_1491"

><td id="1491"><a href="#1491">1491</a></td></tr
><tr id="gr_svn7768_1492"

><td id="1492"><a href="#1492">1492</a></td></tr
><tr id="gr_svn7768_1493"

><td id="1493"><a href="#1493">1493</a></td></tr
><tr id="gr_svn7768_1494"

><td id="1494"><a href="#1494">1494</a></td></tr
><tr id="gr_svn7768_1495"

><td id="1495"><a href="#1495">1495</a></td></tr
><tr id="gr_svn7768_1496"

><td id="1496"><a href="#1496">1496</a></td></tr
><tr id="gr_svn7768_1497"

><td id="1497"><a href="#1497">1497</a></td></tr
><tr id="gr_svn7768_1498"

><td id="1498"><a href="#1498">1498</a></td></tr
><tr id="gr_svn7768_1499"

><td id="1499"><a href="#1499">1499</a></td></tr
><tr id="gr_svn7768_1500"

><td id="1500"><a href="#1500">1500</a></td></tr
><tr id="gr_svn7768_1501"

><td id="1501"><a href="#1501">1501</a></td></tr
><tr id="gr_svn7768_1502"

><td id="1502"><a href="#1502">1502</a></td></tr
><tr id="gr_svn7768_1503"

><td id="1503"><a href="#1503">1503</a></td></tr
><tr id="gr_svn7768_1504"

><td id="1504"><a href="#1504">1504</a></td></tr
><tr id="gr_svn7768_1505"

><td id="1505"><a href="#1505">1505</a></td></tr
><tr id="gr_svn7768_1506"

><td id="1506"><a href="#1506">1506</a></td></tr
><tr id="gr_svn7768_1507"

><td id="1507"><a href="#1507">1507</a></td></tr
><tr id="gr_svn7768_1508"

><td id="1508"><a href="#1508">1508</a></td></tr
><tr id="gr_svn7768_1509"

><td id="1509"><a href="#1509">1509</a></td></tr
><tr id="gr_svn7768_1510"

><td id="1510"><a href="#1510">1510</a></td></tr
><tr id="gr_svn7768_1511"

><td id="1511"><a href="#1511">1511</a></td></tr
><tr id="gr_svn7768_1512"

><td id="1512"><a href="#1512">1512</a></td></tr
><tr id="gr_svn7768_1513"

><td id="1513"><a href="#1513">1513</a></td></tr
><tr id="gr_svn7768_1514"

><td id="1514"><a href="#1514">1514</a></td></tr
><tr id="gr_svn7768_1515"

><td id="1515"><a href="#1515">1515</a></td></tr
><tr id="gr_svn7768_1516"

><td id="1516"><a href="#1516">1516</a></td></tr
><tr id="gr_svn7768_1517"

><td id="1517"><a href="#1517">1517</a></td></tr
><tr id="gr_svn7768_1518"

><td id="1518"><a href="#1518">1518</a></td></tr
><tr id="gr_svn7768_1519"

><td id="1519"><a href="#1519">1519</a></td></tr
><tr id="gr_svn7768_1520"

><td id="1520"><a href="#1520">1520</a></td></tr
><tr id="gr_svn7768_1521"

><td id="1521"><a href="#1521">1521</a></td></tr
><tr id="gr_svn7768_1522"

><td id="1522"><a href="#1522">1522</a></td></tr
><tr id="gr_svn7768_1523"

><td id="1523"><a href="#1523">1523</a></td></tr
><tr id="gr_svn7768_1524"

><td id="1524"><a href="#1524">1524</a></td></tr
><tr id="gr_svn7768_1525"

><td id="1525"><a href="#1525">1525</a></td></tr
><tr id="gr_svn7768_1526"

><td id="1526"><a href="#1526">1526</a></td></tr
><tr id="gr_svn7768_1527"

><td id="1527"><a href="#1527">1527</a></td></tr
><tr id="gr_svn7768_1528"

><td id="1528"><a href="#1528">1528</a></td></tr
><tr id="gr_svn7768_1529"

><td id="1529"><a href="#1529">1529</a></td></tr
><tr id="gr_svn7768_1530"

><td id="1530"><a href="#1530">1530</a></td></tr
><tr id="gr_svn7768_1531"

><td id="1531"><a href="#1531">1531</a></td></tr
><tr id="gr_svn7768_1532"

><td id="1532"><a href="#1532">1532</a></td></tr
><tr id="gr_svn7768_1533"

><td id="1533"><a href="#1533">1533</a></td></tr
><tr id="gr_svn7768_1534"

><td id="1534"><a href="#1534">1534</a></td></tr
><tr id="gr_svn7768_1535"

><td id="1535"><a href="#1535">1535</a></td></tr
><tr id="gr_svn7768_1536"

><td id="1536"><a href="#1536">1536</a></td></tr
><tr id="gr_svn7768_1537"

><td id="1537"><a href="#1537">1537</a></td></tr
><tr id="gr_svn7768_1538"

><td id="1538"><a href="#1538">1538</a></td></tr
><tr id="gr_svn7768_1539"

><td id="1539"><a href="#1539">1539</a></td></tr
><tr id="gr_svn7768_1540"

><td id="1540"><a href="#1540">1540</a></td></tr
><tr id="gr_svn7768_1541"

><td id="1541"><a href="#1541">1541</a></td></tr
><tr id="gr_svn7768_1542"

><td id="1542"><a href="#1542">1542</a></td></tr
><tr id="gr_svn7768_1543"

><td id="1543"><a href="#1543">1543</a></td></tr
><tr id="gr_svn7768_1544"

><td id="1544"><a href="#1544">1544</a></td></tr
><tr id="gr_svn7768_1545"

><td id="1545"><a href="#1545">1545</a></td></tr
><tr id="gr_svn7768_1546"

><td id="1546"><a href="#1546">1546</a></td></tr
><tr id="gr_svn7768_1547"

><td id="1547"><a href="#1547">1547</a></td></tr
><tr id="gr_svn7768_1548"

><td id="1548"><a href="#1548">1548</a></td></tr
><tr id="gr_svn7768_1549"

><td id="1549"><a href="#1549">1549</a></td></tr
><tr id="gr_svn7768_1550"

><td id="1550"><a href="#1550">1550</a></td></tr
><tr id="gr_svn7768_1551"

><td id="1551"><a href="#1551">1551</a></td></tr
><tr id="gr_svn7768_1552"

><td id="1552"><a href="#1552">1552</a></td></tr
><tr id="gr_svn7768_1553"

><td id="1553"><a href="#1553">1553</a></td></tr
><tr id="gr_svn7768_1554"

><td id="1554"><a href="#1554">1554</a></td></tr
><tr id="gr_svn7768_1555"

><td id="1555"><a href="#1555">1555</a></td></tr
><tr id="gr_svn7768_1556"

><td id="1556"><a href="#1556">1556</a></td></tr
><tr id="gr_svn7768_1557"

><td id="1557"><a href="#1557">1557</a></td></tr
><tr id="gr_svn7768_1558"

><td id="1558"><a href="#1558">1558</a></td></tr
><tr id="gr_svn7768_1559"

><td id="1559"><a href="#1559">1559</a></td></tr
><tr id="gr_svn7768_1560"

><td id="1560"><a href="#1560">1560</a></td></tr
><tr id="gr_svn7768_1561"

><td id="1561"><a href="#1561">1561</a></td></tr
><tr id="gr_svn7768_1562"

><td id="1562"><a href="#1562">1562</a></td></tr
><tr id="gr_svn7768_1563"

><td id="1563"><a href="#1563">1563</a></td></tr
><tr id="gr_svn7768_1564"

><td id="1564"><a href="#1564">1564</a></td></tr
><tr id="gr_svn7768_1565"

><td id="1565"><a href="#1565">1565</a></td></tr
><tr id="gr_svn7768_1566"

><td id="1566"><a href="#1566">1566</a></td></tr
><tr id="gr_svn7768_1567"

><td id="1567"><a href="#1567">1567</a></td></tr
><tr id="gr_svn7768_1568"

><td id="1568"><a href="#1568">1568</a></td></tr
><tr id="gr_svn7768_1569"

><td id="1569"><a href="#1569">1569</a></td></tr
><tr id="gr_svn7768_1570"

><td id="1570"><a href="#1570">1570</a></td></tr
><tr id="gr_svn7768_1571"

><td id="1571"><a href="#1571">1571</a></td></tr
><tr id="gr_svn7768_1572"

><td id="1572"><a href="#1572">1572</a></td></tr
><tr id="gr_svn7768_1573"

><td id="1573"><a href="#1573">1573</a></td></tr
><tr id="gr_svn7768_1574"

><td id="1574"><a href="#1574">1574</a></td></tr
><tr id="gr_svn7768_1575"

><td id="1575"><a href="#1575">1575</a></td></tr
><tr id="gr_svn7768_1576"

><td id="1576"><a href="#1576">1576</a></td></tr
><tr id="gr_svn7768_1577"

><td id="1577"><a href="#1577">1577</a></td></tr
><tr id="gr_svn7768_1578"

><td id="1578"><a href="#1578">1578</a></td></tr
><tr id="gr_svn7768_1579"

><td id="1579"><a href="#1579">1579</a></td></tr
><tr id="gr_svn7768_1580"

><td id="1580"><a href="#1580">1580</a></td></tr
><tr id="gr_svn7768_1581"

><td id="1581"><a href="#1581">1581</a></td></tr
><tr id="gr_svn7768_1582"

><td id="1582"><a href="#1582">1582</a></td></tr
><tr id="gr_svn7768_1583"

><td id="1583"><a href="#1583">1583</a></td></tr
><tr id="gr_svn7768_1584"

><td id="1584"><a href="#1584">1584</a></td></tr
><tr id="gr_svn7768_1585"

><td id="1585"><a href="#1585">1585</a></td></tr
><tr id="gr_svn7768_1586"

><td id="1586"><a href="#1586">1586</a></td></tr
><tr id="gr_svn7768_1587"

><td id="1587"><a href="#1587">1587</a></td></tr
><tr id="gr_svn7768_1588"

><td id="1588"><a href="#1588">1588</a></td></tr
><tr id="gr_svn7768_1589"

><td id="1589"><a href="#1589">1589</a></td></tr
><tr id="gr_svn7768_1590"

><td id="1590"><a href="#1590">1590</a></td></tr
><tr id="gr_svn7768_1591"

><td id="1591"><a href="#1591">1591</a></td></tr
><tr id="gr_svn7768_1592"

><td id="1592"><a href="#1592">1592</a></td></tr
><tr id="gr_svn7768_1593"

><td id="1593"><a href="#1593">1593</a></td></tr
><tr id="gr_svn7768_1594"

><td id="1594"><a href="#1594">1594</a></td></tr
><tr id="gr_svn7768_1595"

><td id="1595"><a href="#1595">1595</a></td></tr
><tr id="gr_svn7768_1596"

><td id="1596"><a href="#1596">1596</a></td></tr
><tr id="gr_svn7768_1597"

><td id="1597"><a href="#1597">1597</a></td></tr
><tr id="gr_svn7768_1598"

><td id="1598"><a href="#1598">1598</a></td></tr
><tr id="gr_svn7768_1599"

><td id="1599"><a href="#1599">1599</a></td></tr
><tr id="gr_svn7768_1600"

><td id="1600"><a href="#1600">1600</a></td></tr
><tr id="gr_svn7768_1601"

><td id="1601"><a href="#1601">1601</a></td></tr
><tr id="gr_svn7768_1602"

><td id="1602"><a href="#1602">1602</a></td></tr
><tr id="gr_svn7768_1603"

><td id="1603"><a href="#1603">1603</a></td></tr
><tr id="gr_svn7768_1604"

><td id="1604"><a href="#1604">1604</a></td></tr
><tr id="gr_svn7768_1605"

><td id="1605"><a href="#1605">1605</a></td></tr
><tr id="gr_svn7768_1606"

><td id="1606"><a href="#1606">1606</a></td></tr
><tr id="gr_svn7768_1607"

><td id="1607"><a href="#1607">1607</a></td></tr
><tr id="gr_svn7768_1608"

><td id="1608"><a href="#1608">1608</a></td></tr
><tr id="gr_svn7768_1609"

><td id="1609"><a href="#1609">1609</a></td></tr
><tr id="gr_svn7768_1610"

><td id="1610"><a href="#1610">1610</a></td></tr
><tr id="gr_svn7768_1611"

><td id="1611"><a href="#1611">1611</a></td></tr
><tr id="gr_svn7768_1612"

><td id="1612"><a href="#1612">1612</a></td></tr
><tr id="gr_svn7768_1613"

><td id="1613"><a href="#1613">1613</a></td></tr
><tr id="gr_svn7768_1614"

><td id="1614"><a href="#1614">1614</a></td></tr
><tr id="gr_svn7768_1615"

><td id="1615"><a href="#1615">1615</a></td></tr
><tr id="gr_svn7768_1616"

><td id="1616"><a href="#1616">1616</a></td></tr
><tr id="gr_svn7768_1617"

><td id="1617"><a href="#1617">1617</a></td></tr
><tr id="gr_svn7768_1618"

><td id="1618"><a href="#1618">1618</a></td></tr
><tr id="gr_svn7768_1619"

><td id="1619"><a href="#1619">1619</a></td></tr
><tr id="gr_svn7768_1620"

><td id="1620"><a href="#1620">1620</a></td></tr
><tr id="gr_svn7768_1621"

><td id="1621"><a href="#1621">1621</a></td></tr
><tr id="gr_svn7768_1622"

><td id="1622"><a href="#1622">1622</a></td></tr
><tr id="gr_svn7768_1623"

><td id="1623"><a href="#1623">1623</a></td></tr
><tr id="gr_svn7768_1624"

><td id="1624"><a href="#1624">1624</a></td></tr
><tr id="gr_svn7768_1625"

><td id="1625"><a href="#1625">1625</a></td></tr
><tr id="gr_svn7768_1626"

><td id="1626"><a href="#1626">1626</a></td></tr
><tr id="gr_svn7768_1627"

><td id="1627"><a href="#1627">1627</a></td></tr
><tr id="gr_svn7768_1628"

><td id="1628"><a href="#1628">1628</a></td></tr
><tr id="gr_svn7768_1629"

><td id="1629"><a href="#1629">1629</a></td></tr
><tr id="gr_svn7768_1630"

><td id="1630"><a href="#1630">1630</a></td></tr
><tr id="gr_svn7768_1631"

><td id="1631"><a href="#1631">1631</a></td></tr
><tr id="gr_svn7768_1632"

><td id="1632"><a href="#1632">1632</a></td></tr
><tr id="gr_svn7768_1633"

><td id="1633"><a href="#1633">1633</a></td></tr
><tr id="gr_svn7768_1634"

><td id="1634"><a href="#1634">1634</a></td></tr
><tr id="gr_svn7768_1635"

><td id="1635"><a href="#1635">1635</a></td></tr
><tr id="gr_svn7768_1636"

><td id="1636"><a href="#1636">1636</a></td></tr
><tr id="gr_svn7768_1637"

><td id="1637"><a href="#1637">1637</a></td></tr
><tr id="gr_svn7768_1638"

><td id="1638"><a href="#1638">1638</a></td></tr
><tr id="gr_svn7768_1639"

><td id="1639"><a href="#1639">1639</a></td></tr
><tr id="gr_svn7768_1640"

><td id="1640"><a href="#1640">1640</a></td></tr
><tr id="gr_svn7768_1641"

><td id="1641"><a href="#1641">1641</a></td></tr
><tr id="gr_svn7768_1642"

><td id="1642"><a href="#1642">1642</a></td></tr
><tr id="gr_svn7768_1643"

><td id="1643"><a href="#1643">1643</a></td></tr
><tr id="gr_svn7768_1644"

><td id="1644"><a href="#1644">1644</a></td></tr
><tr id="gr_svn7768_1645"

><td id="1645"><a href="#1645">1645</a></td></tr
><tr id="gr_svn7768_1646"

><td id="1646"><a href="#1646">1646</a></td></tr
><tr id="gr_svn7768_1647"

><td id="1647"><a href="#1647">1647</a></td></tr
><tr id="gr_svn7768_1648"

><td id="1648"><a href="#1648">1648</a></td></tr
><tr id="gr_svn7768_1649"

><td id="1649"><a href="#1649">1649</a></td></tr
><tr id="gr_svn7768_1650"

><td id="1650"><a href="#1650">1650</a></td></tr
><tr id="gr_svn7768_1651"

><td id="1651"><a href="#1651">1651</a></td></tr
><tr id="gr_svn7768_1652"

><td id="1652"><a href="#1652">1652</a></td></tr
><tr id="gr_svn7768_1653"

><td id="1653"><a href="#1653">1653</a></td></tr
><tr id="gr_svn7768_1654"

><td id="1654"><a href="#1654">1654</a></td></tr
><tr id="gr_svn7768_1655"

><td id="1655"><a href="#1655">1655</a></td></tr
><tr id="gr_svn7768_1656"

><td id="1656"><a href="#1656">1656</a></td></tr
><tr id="gr_svn7768_1657"

><td id="1657"><a href="#1657">1657</a></td></tr
><tr id="gr_svn7768_1658"

><td id="1658"><a href="#1658">1658</a></td></tr
><tr id="gr_svn7768_1659"

><td id="1659"><a href="#1659">1659</a></td></tr
><tr id="gr_svn7768_1660"

><td id="1660"><a href="#1660">1660</a></td></tr
><tr id="gr_svn7768_1661"

><td id="1661"><a href="#1661">1661</a></td></tr
><tr id="gr_svn7768_1662"

><td id="1662"><a href="#1662">1662</a></td></tr
><tr id="gr_svn7768_1663"

><td id="1663"><a href="#1663">1663</a></td></tr
><tr id="gr_svn7768_1664"

><td id="1664"><a href="#1664">1664</a></td></tr
><tr id="gr_svn7768_1665"

><td id="1665"><a href="#1665">1665</a></td></tr
><tr id="gr_svn7768_1666"

><td id="1666"><a href="#1666">1666</a></td></tr
><tr id="gr_svn7768_1667"

><td id="1667"><a href="#1667">1667</a></td></tr
><tr id="gr_svn7768_1668"

><td id="1668"><a href="#1668">1668</a></td></tr
><tr id="gr_svn7768_1669"

><td id="1669"><a href="#1669">1669</a></td></tr
><tr id="gr_svn7768_1670"

><td id="1670"><a href="#1670">1670</a></td></tr
><tr id="gr_svn7768_1671"

><td id="1671"><a href="#1671">1671</a></td></tr
><tr id="gr_svn7768_1672"

><td id="1672"><a href="#1672">1672</a></td></tr
><tr id="gr_svn7768_1673"

><td id="1673"><a href="#1673">1673</a></td></tr
><tr id="gr_svn7768_1674"

><td id="1674"><a href="#1674">1674</a></td></tr
><tr id="gr_svn7768_1675"

><td id="1675"><a href="#1675">1675</a></td></tr
><tr id="gr_svn7768_1676"

><td id="1676"><a href="#1676">1676</a></td></tr
><tr id="gr_svn7768_1677"

><td id="1677"><a href="#1677">1677</a></td></tr
><tr id="gr_svn7768_1678"

><td id="1678"><a href="#1678">1678</a></td></tr
><tr id="gr_svn7768_1679"

><td id="1679"><a href="#1679">1679</a></td></tr
><tr id="gr_svn7768_1680"

><td id="1680"><a href="#1680">1680</a></td></tr
><tr id="gr_svn7768_1681"

><td id="1681"><a href="#1681">1681</a></td></tr
><tr id="gr_svn7768_1682"

><td id="1682"><a href="#1682">1682</a></td></tr
><tr id="gr_svn7768_1683"

><td id="1683"><a href="#1683">1683</a></td></tr
><tr id="gr_svn7768_1684"

><td id="1684"><a href="#1684">1684</a></td></tr
><tr id="gr_svn7768_1685"

><td id="1685"><a href="#1685">1685</a></td></tr
><tr id="gr_svn7768_1686"

><td id="1686"><a href="#1686">1686</a></td></tr
><tr id="gr_svn7768_1687"

><td id="1687"><a href="#1687">1687</a></td></tr
><tr id="gr_svn7768_1688"

><td id="1688"><a href="#1688">1688</a></td></tr
><tr id="gr_svn7768_1689"

><td id="1689"><a href="#1689">1689</a></td></tr
><tr id="gr_svn7768_1690"

><td id="1690"><a href="#1690">1690</a></td></tr
><tr id="gr_svn7768_1691"

><td id="1691"><a href="#1691">1691</a></td></tr
><tr id="gr_svn7768_1692"

><td id="1692"><a href="#1692">1692</a></td></tr
><tr id="gr_svn7768_1693"

><td id="1693"><a href="#1693">1693</a></td></tr
><tr id="gr_svn7768_1694"

><td id="1694"><a href="#1694">1694</a></td></tr
><tr id="gr_svn7768_1695"

><td id="1695"><a href="#1695">1695</a></td></tr
><tr id="gr_svn7768_1696"

><td id="1696"><a href="#1696">1696</a></td></tr
><tr id="gr_svn7768_1697"

><td id="1697"><a href="#1697">1697</a></td></tr
><tr id="gr_svn7768_1698"

><td id="1698"><a href="#1698">1698</a></td></tr
><tr id="gr_svn7768_1699"

><td id="1699"><a href="#1699">1699</a></td></tr
><tr id="gr_svn7768_1700"

><td id="1700"><a href="#1700">1700</a></td></tr
><tr id="gr_svn7768_1701"

><td id="1701"><a href="#1701">1701</a></td></tr
><tr id="gr_svn7768_1702"

><td id="1702"><a href="#1702">1702</a></td></tr
><tr id="gr_svn7768_1703"

><td id="1703"><a href="#1703">1703</a></td></tr
><tr id="gr_svn7768_1704"

><td id="1704"><a href="#1704">1704</a></td></tr
><tr id="gr_svn7768_1705"

><td id="1705"><a href="#1705">1705</a></td></tr
><tr id="gr_svn7768_1706"

><td id="1706"><a href="#1706">1706</a></td></tr
><tr id="gr_svn7768_1707"

><td id="1707"><a href="#1707">1707</a></td></tr
><tr id="gr_svn7768_1708"

><td id="1708"><a href="#1708">1708</a></td></tr
><tr id="gr_svn7768_1709"

><td id="1709"><a href="#1709">1709</a></td></tr
><tr id="gr_svn7768_1710"

><td id="1710"><a href="#1710">1710</a></td></tr
><tr id="gr_svn7768_1711"

><td id="1711"><a href="#1711">1711</a></td></tr
><tr id="gr_svn7768_1712"

><td id="1712"><a href="#1712">1712</a></td></tr
><tr id="gr_svn7768_1713"

><td id="1713"><a href="#1713">1713</a></td></tr
><tr id="gr_svn7768_1714"

><td id="1714"><a href="#1714">1714</a></td></tr
><tr id="gr_svn7768_1715"

><td id="1715"><a href="#1715">1715</a></td></tr
><tr id="gr_svn7768_1716"

><td id="1716"><a href="#1716">1716</a></td></tr
><tr id="gr_svn7768_1717"

><td id="1717"><a href="#1717">1717</a></td></tr
><tr id="gr_svn7768_1718"

><td id="1718"><a href="#1718">1718</a></td></tr
><tr id="gr_svn7768_1719"

><td id="1719"><a href="#1719">1719</a></td></tr
><tr id="gr_svn7768_1720"

><td id="1720"><a href="#1720">1720</a></td></tr
><tr id="gr_svn7768_1721"

><td id="1721"><a href="#1721">1721</a></td></tr
><tr id="gr_svn7768_1722"

><td id="1722"><a href="#1722">1722</a></td></tr
><tr id="gr_svn7768_1723"

><td id="1723"><a href="#1723">1723</a></td></tr
><tr id="gr_svn7768_1724"

><td id="1724"><a href="#1724">1724</a></td></tr
><tr id="gr_svn7768_1725"

><td id="1725"><a href="#1725">1725</a></td></tr
><tr id="gr_svn7768_1726"

><td id="1726"><a href="#1726">1726</a></td></tr
><tr id="gr_svn7768_1727"

><td id="1727"><a href="#1727">1727</a></td></tr
><tr id="gr_svn7768_1728"

><td id="1728"><a href="#1728">1728</a></td></tr
><tr id="gr_svn7768_1729"

><td id="1729"><a href="#1729">1729</a></td></tr
><tr id="gr_svn7768_1730"

><td id="1730"><a href="#1730">1730</a></td></tr
><tr id="gr_svn7768_1731"

><td id="1731"><a href="#1731">1731</a></td></tr
><tr id="gr_svn7768_1732"

><td id="1732"><a href="#1732">1732</a></td></tr
><tr id="gr_svn7768_1733"

><td id="1733"><a href="#1733">1733</a></td></tr
><tr id="gr_svn7768_1734"

><td id="1734"><a href="#1734">1734</a></td></tr
><tr id="gr_svn7768_1735"

><td id="1735"><a href="#1735">1735</a></td></tr
><tr id="gr_svn7768_1736"

><td id="1736"><a href="#1736">1736</a></td></tr
><tr id="gr_svn7768_1737"

><td id="1737"><a href="#1737">1737</a></td></tr
><tr id="gr_svn7768_1738"

><td id="1738"><a href="#1738">1738</a></td></tr
><tr id="gr_svn7768_1739"

><td id="1739"><a href="#1739">1739</a></td></tr
><tr id="gr_svn7768_1740"

><td id="1740"><a href="#1740">1740</a></td></tr
><tr id="gr_svn7768_1741"

><td id="1741"><a href="#1741">1741</a></td></tr
><tr id="gr_svn7768_1742"

><td id="1742"><a href="#1742">1742</a></td></tr
><tr id="gr_svn7768_1743"

><td id="1743"><a href="#1743">1743</a></td></tr
><tr id="gr_svn7768_1744"

><td id="1744"><a href="#1744">1744</a></td></tr
><tr id="gr_svn7768_1745"

><td id="1745"><a href="#1745">1745</a></td></tr
><tr id="gr_svn7768_1746"

><td id="1746"><a href="#1746">1746</a></td></tr
><tr id="gr_svn7768_1747"

><td id="1747"><a href="#1747">1747</a></td></tr
><tr id="gr_svn7768_1748"

><td id="1748"><a href="#1748">1748</a></td></tr
><tr id="gr_svn7768_1749"

><td id="1749"><a href="#1749">1749</a></td></tr
><tr id="gr_svn7768_1750"

><td id="1750"><a href="#1750">1750</a></td></tr
><tr id="gr_svn7768_1751"

><td id="1751"><a href="#1751">1751</a></td></tr
><tr id="gr_svn7768_1752"

><td id="1752"><a href="#1752">1752</a></td></tr
><tr id="gr_svn7768_1753"

><td id="1753"><a href="#1753">1753</a></td></tr
><tr id="gr_svn7768_1754"

><td id="1754"><a href="#1754">1754</a></td></tr
><tr id="gr_svn7768_1755"

><td id="1755"><a href="#1755">1755</a></td></tr
><tr id="gr_svn7768_1756"

><td id="1756"><a href="#1756">1756</a></td></tr
><tr id="gr_svn7768_1757"

><td id="1757"><a href="#1757">1757</a></td></tr
><tr id="gr_svn7768_1758"

><td id="1758"><a href="#1758">1758</a></td></tr
><tr id="gr_svn7768_1759"

><td id="1759"><a href="#1759">1759</a></td></tr
><tr id="gr_svn7768_1760"

><td id="1760"><a href="#1760">1760</a></td></tr
><tr id="gr_svn7768_1761"

><td id="1761"><a href="#1761">1761</a></td></tr
><tr id="gr_svn7768_1762"

><td id="1762"><a href="#1762">1762</a></td></tr
><tr id="gr_svn7768_1763"

><td id="1763"><a href="#1763">1763</a></td></tr
><tr id="gr_svn7768_1764"

><td id="1764"><a href="#1764">1764</a></td></tr
><tr id="gr_svn7768_1765"

><td id="1765"><a href="#1765">1765</a></td></tr
><tr id="gr_svn7768_1766"

><td id="1766"><a href="#1766">1766</a></td></tr
><tr id="gr_svn7768_1767"

><td id="1767"><a href="#1767">1767</a></td></tr
><tr id="gr_svn7768_1768"

><td id="1768"><a href="#1768">1768</a></td></tr
><tr id="gr_svn7768_1769"

><td id="1769"><a href="#1769">1769</a></td></tr
><tr id="gr_svn7768_1770"

><td id="1770"><a href="#1770">1770</a></td></tr
><tr id="gr_svn7768_1771"

><td id="1771"><a href="#1771">1771</a></td></tr
><tr id="gr_svn7768_1772"

><td id="1772"><a href="#1772">1772</a></td></tr
><tr id="gr_svn7768_1773"

><td id="1773"><a href="#1773">1773</a></td></tr
><tr id="gr_svn7768_1774"

><td id="1774"><a href="#1774">1774</a></td></tr
><tr id="gr_svn7768_1775"

><td id="1775"><a href="#1775">1775</a></td></tr
><tr id="gr_svn7768_1776"

><td id="1776"><a href="#1776">1776</a></td></tr
><tr id="gr_svn7768_1777"

><td id="1777"><a href="#1777">1777</a></td></tr
><tr id="gr_svn7768_1778"

><td id="1778"><a href="#1778">1778</a></td></tr
><tr id="gr_svn7768_1779"

><td id="1779"><a href="#1779">1779</a></td></tr
><tr id="gr_svn7768_1780"

><td id="1780"><a href="#1780">1780</a></td></tr
><tr id="gr_svn7768_1781"

><td id="1781"><a href="#1781">1781</a></td></tr
><tr id="gr_svn7768_1782"

><td id="1782"><a href="#1782">1782</a></td></tr
><tr id="gr_svn7768_1783"

><td id="1783"><a href="#1783">1783</a></td></tr
><tr id="gr_svn7768_1784"

><td id="1784"><a href="#1784">1784</a></td></tr
><tr id="gr_svn7768_1785"

><td id="1785"><a href="#1785">1785</a></td></tr
><tr id="gr_svn7768_1786"

><td id="1786"><a href="#1786">1786</a></td></tr
><tr id="gr_svn7768_1787"

><td id="1787"><a href="#1787">1787</a></td></tr
><tr id="gr_svn7768_1788"

><td id="1788"><a href="#1788">1788</a></td></tr
><tr id="gr_svn7768_1789"

><td id="1789"><a href="#1789">1789</a></td></tr
><tr id="gr_svn7768_1790"

><td id="1790"><a href="#1790">1790</a></td></tr
><tr id="gr_svn7768_1791"

><td id="1791"><a href="#1791">1791</a></td></tr
><tr id="gr_svn7768_1792"

><td id="1792"><a href="#1792">1792</a></td></tr
><tr id="gr_svn7768_1793"

><td id="1793"><a href="#1793">1793</a></td></tr
><tr id="gr_svn7768_1794"

><td id="1794"><a href="#1794">1794</a></td></tr
><tr id="gr_svn7768_1795"

><td id="1795"><a href="#1795">1795</a></td></tr
><tr id="gr_svn7768_1796"

><td id="1796"><a href="#1796">1796</a></td></tr
><tr id="gr_svn7768_1797"

><td id="1797"><a href="#1797">1797</a></td></tr
><tr id="gr_svn7768_1798"

><td id="1798"><a href="#1798">1798</a></td></tr
><tr id="gr_svn7768_1799"

><td id="1799"><a href="#1799">1799</a></td></tr
><tr id="gr_svn7768_1800"

><td id="1800"><a href="#1800">1800</a></td></tr
><tr id="gr_svn7768_1801"

><td id="1801"><a href="#1801">1801</a></td></tr
><tr id="gr_svn7768_1802"

><td id="1802"><a href="#1802">1802</a></td></tr
><tr id="gr_svn7768_1803"

><td id="1803"><a href="#1803">1803</a></td></tr
><tr id="gr_svn7768_1804"

><td id="1804"><a href="#1804">1804</a></td></tr
><tr id="gr_svn7768_1805"

><td id="1805"><a href="#1805">1805</a></td></tr
><tr id="gr_svn7768_1806"

><td id="1806"><a href="#1806">1806</a></td></tr
><tr id="gr_svn7768_1807"

><td id="1807"><a href="#1807">1807</a></td></tr
><tr id="gr_svn7768_1808"

><td id="1808"><a href="#1808">1808</a></td></tr
><tr id="gr_svn7768_1809"

><td id="1809"><a href="#1809">1809</a></td></tr
><tr id="gr_svn7768_1810"

><td id="1810"><a href="#1810">1810</a></td></tr
><tr id="gr_svn7768_1811"

><td id="1811"><a href="#1811">1811</a></td></tr
><tr id="gr_svn7768_1812"

><td id="1812"><a href="#1812">1812</a></td></tr
><tr id="gr_svn7768_1813"

><td id="1813"><a href="#1813">1813</a></td></tr
><tr id="gr_svn7768_1814"

><td id="1814"><a href="#1814">1814</a></td></tr
><tr id="gr_svn7768_1815"

><td id="1815"><a href="#1815">1815</a></td></tr
><tr id="gr_svn7768_1816"

><td id="1816"><a href="#1816">1816</a></td></tr
><tr id="gr_svn7768_1817"

><td id="1817"><a href="#1817">1817</a></td></tr
><tr id="gr_svn7768_1818"

><td id="1818"><a href="#1818">1818</a></td></tr
><tr id="gr_svn7768_1819"

><td id="1819"><a href="#1819">1819</a></td></tr
><tr id="gr_svn7768_1820"

><td id="1820"><a href="#1820">1820</a></td></tr
><tr id="gr_svn7768_1821"

><td id="1821"><a href="#1821">1821</a></td></tr
><tr id="gr_svn7768_1822"

><td id="1822"><a href="#1822">1822</a></td></tr
><tr id="gr_svn7768_1823"

><td id="1823"><a href="#1823">1823</a></td></tr
><tr id="gr_svn7768_1824"

><td id="1824"><a href="#1824">1824</a></td></tr
><tr id="gr_svn7768_1825"

><td id="1825"><a href="#1825">1825</a></td></tr
><tr id="gr_svn7768_1826"

><td id="1826"><a href="#1826">1826</a></td></tr
><tr id="gr_svn7768_1827"

><td id="1827"><a href="#1827">1827</a></td></tr
><tr id="gr_svn7768_1828"

><td id="1828"><a href="#1828">1828</a></td></tr
><tr id="gr_svn7768_1829"

><td id="1829"><a href="#1829">1829</a></td></tr
><tr id="gr_svn7768_1830"

><td id="1830"><a href="#1830">1830</a></td></tr
><tr id="gr_svn7768_1831"

><td id="1831"><a href="#1831">1831</a></td></tr
><tr id="gr_svn7768_1832"

><td id="1832"><a href="#1832">1832</a></td></tr
><tr id="gr_svn7768_1833"

><td id="1833"><a href="#1833">1833</a></td></tr
><tr id="gr_svn7768_1834"

><td id="1834"><a href="#1834">1834</a></td></tr
><tr id="gr_svn7768_1835"

><td id="1835"><a href="#1835">1835</a></td></tr
><tr id="gr_svn7768_1836"

><td id="1836"><a href="#1836">1836</a></td></tr
><tr id="gr_svn7768_1837"

><td id="1837"><a href="#1837">1837</a></td></tr
><tr id="gr_svn7768_1838"

><td id="1838"><a href="#1838">1838</a></td></tr
><tr id="gr_svn7768_1839"

><td id="1839"><a href="#1839">1839</a></td></tr
><tr id="gr_svn7768_1840"

><td id="1840"><a href="#1840">1840</a></td></tr
><tr id="gr_svn7768_1841"

><td id="1841"><a href="#1841">1841</a></td></tr
><tr id="gr_svn7768_1842"

><td id="1842"><a href="#1842">1842</a></td></tr
><tr id="gr_svn7768_1843"

><td id="1843"><a href="#1843">1843</a></td></tr
><tr id="gr_svn7768_1844"

><td id="1844"><a href="#1844">1844</a></td></tr
><tr id="gr_svn7768_1845"

><td id="1845"><a href="#1845">1845</a></td></tr
><tr id="gr_svn7768_1846"

><td id="1846"><a href="#1846">1846</a></td></tr
><tr id="gr_svn7768_1847"

><td id="1847"><a href="#1847">1847</a></td></tr
><tr id="gr_svn7768_1848"

><td id="1848"><a href="#1848">1848</a></td></tr
><tr id="gr_svn7768_1849"

><td id="1849"><a href="#1849">1849</a></td></tr
><tr id="gr_svn7768_1850"

><td id="1850"><a href="#1850">1850</a></td></tr
><tr id="gr_svn7768_1851"

><td id="1851"><a href="#1851">1851</a></td></tr
><tr id="gr_svn7768_1852"

><td id="1852"><a href="#1852">1852</a></td></tr
><tr id="gr_svn7768_1853"

><td id="1853"><a href="#1853">1853</a></td></tr
><tr id="gr_svn7768_1854"

><td id="1854"><a href="#1854">1854</a></td></tr
><tr id="gr_svn7768_1855"

><td id="1855"><a href="#1855">1855</a></td></tr
><tr id="gr_svn7768_1856"

><td id="1856"><a href="#1856">1856</a></td></tr
><tr id="gr_svn7768_1857"

><td id="1857"><a href="#1857">1857</a></td></tr
><tr id="gr_svn7768_1858"

><td id="1858"><a href="#1858">1858</a></td></tr
><tr id="gr_svn7768_1859"

><td id="1859"><a href="#1859">1859</a></td></tr
><tr id="gr_svn7768_1860"

><td id="1860"><a href="#1860">1860</a></td></tr
><tr id="gr_svn7768_1861"

><td id="1861"><a href="#1861">1861</a></td></tr
><tr id="gr_svn7768_1862"

><td id="1862"><a href="#1862">1862</a></td></tr
><tr id="gr_svn7768_1863"

><td id="1863"><a href="#1863">1863</a></td></tr
><tr id="gr_svn7768_1864"

><td id="1864"><a href="#1864">1864</a></td></tr
><tr id="gr_svn7768_1865"

><td id="1865"><a href="#1865">1865</a></td></tr
><tr id="gr_svn7768_1866"

><td id="1866"><a href="#1866">1866</a></td></tr
><tr id="gr_svn7768_1867"

><td id="1867"><a href="#1867">1867</a></td></tr
><tr id="gr_svn7768_1868"

><td id="1868"><a href="#1868">1868</a></td></tr
><tr id="gr_svn7768_1869"

><td id="1869"><a href="#1869">1869</a></td></tr
><tr id="gr_svn7768_1870"

><td id="1870"><a href="#1870">1870</a></td></tr
><tr id="gr_svn7768_1871"

><td id="1871"><a href="#1871">1871</a></td></tr
><tr id="gr_svn7768_1872"

><td id="1872"><a href="#1872">1872</a></td></tr
><tr id="gr_svn7768_1873"

><td id="1873"><a href="#1873">1873</a></td></tr
><tr id="gr_svn7768_1874"

><td id="1874"><a href="#1874">1874</a></td></tr
><tr id="gr_svn7768_1875"

><td id="1875"><a href="#1875">1875</a></td></tr
><tr id="gr_svn7768_1876"

><td id="1876"><a href="#1876">1876</a></td></tr
><tr id="gr_svn7768_1877"

><td id="1877"><a href="#1877">1877</a></td></tr
><tr id="gr_svn7768_1878"

><td id="1878"><a href="#1878">1878</a></td></tr
><tr id="gr_svn7768_1879"

><td id="1879"><a href="#1879">1879</a></td></tr
><tr id="gr_svn7768_1880"

><td id="1880"><a href="#1880">1880</a></td></tr
><tr id="gr_svn7768_1881"

><td id="1881"><a href="#1881">1881</a></td></tr
><tr id="gr_svn7768_1882"

><td id="1882"><a href="#1882">1882</a></td></tr
><tr id="gr_svn7768_1883"

><td id="1883"><a href="#1883">1883</a></td></tr
><tr id="gr_svn7768_1884"

><td id="1884"><a href="#1884">1884</a></td></tr
><tr id="gr_svn7768_1885"

><td id="1885"><a href="#1885">1885</a></td></tr
><tr id="gr_svn7768_1886"

><td id="1886"><a href="#1886">1886</a></td></tr
><tr id="gr_svn7768_1887"

><td id="1887"><a href="#1887">1887</a></td></tr
><tr id="gr_svn7768_1888"

><td id="1888"><a href="#1888">1888</a></td></tr
><tr id="gr_svn7768_1889"

><td id="1889"><a href="#1889">1889</a></td></tr
><tr id="gr_svn7768_1890"

><td id="1890"><a href="#1890">1890</a></td></tr
><tr id="gr_svn7768_1891"

><td id="1891"><a href="#1891">1891</a></td></tr
><tr id="gr_svn7768_1892"

><td id="1892"><a href="#1892">1892</a></td></tr
><tr id="gr_svn7768_1893"

><td id="1893"><a href="#1893">1893</a></td></tr
><tr id="gr_svn7768_1894"

><td id="1894"><a href="#1894">1894</a></td></tr
><tr id="gr_svn7768_1895"

><td id="1895"><a href="#1895">1895</a></td></tr
><tr id="gr_svn7768_1896"

><td id="1896"><a href="#1896">1896</a></td></tr
><tr id="gr_svn7768_1897"

><td id="1897"><a href="#1897">1897</a></td></tr
><tr id="gr_svn7768_1898"

><td id="1898"><a href="#1898">1898</a></td></tr
><tr id="gr_svn7768_1899"

><td id="1899"><a href="#1899">1899</a></td></tr
><tr id="gr_svn7768_1900"

><td id="1900"><a href="#1900">1900</a></td></tr
><tr id="gr_svn7768_1901"

><td id="1901"><a href="#1901">1901</a></td></tr
><tr id="gr_svn7768_1902"

><td id="1902"><a href="#1902">1902</a></td></tr
><tr id="gr_svn7768_1903"

><td id="1903"><a href="#1903">1903</a></td></tr
><tr id="gr_svn7768_1904"

><td id="1904"><a href="#1904">1904</a></td></tr
><tr id="gr_svn7768_1905"

><td id="1905"><a href="#1905">1905</a></td></tr
><tr id="gr_svn7768_1906"

><td id="1906"><a href="#1906">1906</a></td></tr
><tr id="gr_svn7768_1907"

><td id="1907"><a href="#1907">1907</a></td></tr
><tr id="gr_svn7768_1908"

><td id="1908"><a href="#1908">1908</a></td></tr
><tr id="gr_svn7768_1909"

><td id="1909"><a href="#1909">1909</a></td></tr
><tr id="gr_svn7768_1910"

><td id="1910"><a href="#1910">1910</a></td></tr
><tr id="gr_svn7768_1911"

><td id="1911"><a href="#1911">1911</a></td></tr
><tr id="gr_svn7768_1912"

><td id="1912"><a href="#1912">1912</a></td></tr
><tr id="gr_svn7768_1913"

><td id="1913"><a href="#1913">1913</a></td></tr
><tr id="gr_svn7768_1914"

><td id="1914"><a href="#1914">1914</a></td></tr
><tr id="gr_svn7768_1915"

><td id="1915"><a href="#1915">1915</a></td></tr
><tr id="gr_svn7768_1916"

><td id="1916"><a href="#1916">1916</a></td></tr
><tr id="gr_svn7768_1917"

><td id="1917"><a href="#1917">1917</a></td></tr
><tr id="gr_svn7768_1918"

><td id="1918"><a href="#1918">1918</a></td></tr
><tr id="gr_svn7768_1919"

><td id="1919"><a href="#1919">1919</a></td></tr
><tr id="gr_svn7768_1920"

><td id="1920"><a href="#1920">1920</a></td></tr
><tr id="gr_svn7768_1921"

><td id="1921"><a href="#1921">1921</a></td></tr
><tr id="gr_svn7768_1922"

><td id="1922"><a href="#1922">1922</a></td></tr
><tr id="gr_svn7768_1923"

><td id="1923"><a href="#1923">1923</a></td></tr
><tr id="gr_svn7768_1924"

><td id="1924"><a href="#1924">1924</a></td></tr
><tr id="gr_svn7768_1925"

><td id="1925"><a href="#1925">1925</a></td></tr
><tr id="gr_svn7768_1926"

><td id="1926"><a href="#1926">1926</a></td></tr
><tr id="gr_svn7768_1927"

><td id="1927"><a href="#1927">1927</a></td></tr
><tr id="gr_svn7768_1928"

><td id="1928"><a href="#1928">1928</a></td></tr
><tr id="gr_svn7768_1929"

><td id="1929"><a href="#1929">1929</a></td></tr
><tr id="gr_svn7768_1930"

><td id="1930"><a href="#1930">1930</a></td></tr
><tr id="gr_svn7768_1931"

><td id="1931"><a href="#1931">1931</a></td></tr
><tr id="gr_svn7768_1932"

><td id="1932"><a href="#1932">1932</a></td></tr
><tr id="gr_svn7768_1933"

><td id="1933"><a href="#1933">1933</a></td></tr
><tr id="gr_svn7768_1934"

><td id="1934"><a href="#1934">1934</a></td></tr
><tr id="gr_svn7768_1935"

><td id="1935"><a href="#1935">1935</a></td></tr
><tr id="gr_svn7768_1936"

><td id="1936"><a href="#1936">1936</a></td></tr
><tr id="gr_svn7768_1937"

><td id="1937"><a href="#1937">1937</a></td></tr
><tr id="gr_svn7768_1938"

><td id="1938"><a href="#1938">1938</a></td></tr
><tr id="gr_svn7768_1939"

><td id="1939"><a href="#1939">1939</a></td></tr
><tr id="gr_svn7768_1940"

><td id="1940"><a href="#1940">1940</a></td></tr
><tr id="gr_svn7768_1941"

><td id="1941"><a href="#1941">1941</a></td></tr
><tr id="gr_svn7768_1942"

><td id="1942"><a href="#1942">1942</a></td></tr
><tr id="gr_svn7768_1943"

><td id="1943"><a href="#1943">1943</a></td></tr
><tr id="gr_svn7768_1944"

><td id="1944"><a href="#1944">1944</a></td></tr
><tr id="gr_svn7768_1945"

><td id="1945"><a href="#1945">1945</a></td></tr
><tr id="gr_svn7768_1946"

><td id="1946"><a href="#1946">1946</a></td></tr
><tr id="gr_svn7768_1947"

><td id="1947"><a href="#1947">1947</a></td></tr
><tr id="gr_svn7768_1948"

><td id="1948"><a href="#1948">1948</a></td></tr
><tr id="gr_svn7768_1949"

><td id="1949"><a href="#1949">1949</a></td></tr
><tr id="gr_svn7768_1950"

><td id="1950"><a href="#1950">1950</a></td></tr
><tr id="gr_svn7768_1951"

><td id="1951"><a href="#1951">1951</a></td></tr
><tr id="gr_svn7768_1952"

><td id="1952"><a href="#1952">1952</a></td></tr
><tr id="gr_svn7768_1953"

><td id="1953"><a href="#1953">1953</a></td></tr
><tr id="gr_svn7768_1954"

><td id="1954"><a href="#1954">1954</a></td></tr
><tr id="gr_svn7768_1955"

><td id="1955"><a href="#1955">1955</a></td></tr
><tr id="gr_svn7768_1956"

><td id="1956"><a href="#1956">1956</a></td></tr
><tr id="gr_svn7768_1957"

><td id="1957"><a href="#1957">1957</a></td></tr
><tr id="gr_svn7768_1958"

><td id="1958"><a href="#1958">1958</a></td></tr
><tr id="gr_svn7768_1959"

><td id="1959"><a href="#1959">1959</a></td></tr
><tr id="gr_svn7768_1960"

><td id="1960"><a href="#1960">1960</a></td></tr
><tr id="gr_svn7768_1961"

><td id="1961"><a href="#1961">1961</a></td></tr
><tr id="gr_svn7768_1962"

><td id="1962"><a href="#1962">1962</a></td></tr
><tr id="gr_svn7768_1963"

><td id="1963"><a href="#1963">1963</a></td></tr
><tr id="gr_svn7768_1964"

><td id="1964"><a href="#1964">1964</a></td></tr
><tr id="gr_svn7768_1965"

><td id="1965"><a href="#1965">1965</a></td></tr
><tr id="gr_svn7768_1966"

><td id="1966"><a href="#1966">1966</a></td></tr
><tr id="gr_svn7768_1967"

><td id="1967"><a href="#1967">1967</a></td></tr
><tr id="gr_svn7768_1968"

><td id="1968"><a href="#1968">1968</a></td></tr
><tr id="gr_svn7768_1969"

><td id="1969"><a href="#1969">1969</a></td></tr
><tr id="gr_svn7768_1970"

><td id="1970"><a href="#1970">1970</a></td></tr
><tr id="gr_svn7768_1971"

><td id="1971"><a href="#1971">1971</a></td></tr
><tr id="gr_svn7768_1972"

><td id="1972"><a href="#1972">1972</a></td></tr
><tr id="gr_svn7768_1973"

><td id="1973"><a href="#1973">1973</a></td></tr
><tr id="gr_svn7768_1974"

><td id="1974"><a href="#1974">1974</a></td></tr
><tr id="gr_svn7768_1975"

><td id="1975"><a href="#1975">1975</a></td></tr
><tr id="gr_svn7768_1976"

><td id="1976"><a href="#1976">1976</a></td></tr
><tr id="gr_svn7768_1977"

><td id="1977"><a href="#1977">1977</a></td></tr
><tr id="gr_svn7768_1978"

><td id="1978"><a href="#1978">1978</a></td></tr
><tr id="gr_svn7768_1979"

><td id="1979"><a href="#1979">1979</a></td></tr
><tr id="gr_svn7768_1980"

><td id="1980"><a href="#1980">1980</a></td></tr
><tr id="gr_svn7768_1981"

><td id="1981"><a href="#1981">1981</a></td></tr
><tr id="gr_svn7768_1982"

><td id="1982"><a href="#1982">1982</a></td></tr
><tr id="gr_svn7768_1983"

><td id="1983"><a href="#1983">1983</a></td></tr
><tr id="gr_svn7768_1984"

><td id="1984"><a href="#1984">1984</a></td></tr
><tr id="gr_svn7768_1985"

><td id="1985"><a href="#1985">1985</a></td></tr
><tr id="gr_svn7768_1986"

><td id="1986"><a href="#1986">1986</a></td></tr
><tr id="gr_svn7768_1987"

><td id="1987"><a href="#1987">1987</a></td></tr
><tr id="gr_svn7768_1988"

><td id="1988"><a href="#1988">1988</a></td></tr
><tr id="gr_svn7768_1989"

><td id="1989"><a href="#1989">1989</a></td></tr
><tr id="gr_svn7768_1990"

><td id="1990"><a href="#1990">1990</a></td></tr
><tr id="gr_svn7768_1991"

><td id="1991"><a href="#1991">1991</a></td></tr
><tr id="gr_svn7768_1992"

><td id="1992"><a href="#1992">1992</a></td></tr
><tr id="gr_svn7768_1993"

><td id="1993"><a href="#1993">1993</a></td></tr
><tr id="gr_svn7768_1994"

><td id="1994"><a href="#1994">1994</a></td></tr
><tr id="gr_svn7768_1995"

><td id="1995"><a href="#1995">1995</a></td></tr
><tr id="gr_svn7768_1996"

><td id="1996"><a href="#1996">1996</a></td></tr
><tr id="gr_svn7768_1997"

><td id="1997"><a href="#1997">1997</a></td></tr
><tr id="gr_svn7768_1998"

><td id="1998"><a href="#1998">1998</a></td></tr
><tr id="gr_svn7768_1999"

><td id="1999"><a href="#1999">1999</a></td></tr
><tr id="gr_svn7768_2000"

><td id="2000"><a href="#2000">2000</a></td></tr
><tr id="gr_svn7768_2001"

><td id="2001"><a href="#2001">2001</a></td></tr
><tr id="gr_svn7768_2002"

><td id="2002"><a href="#2002">2002</a></td></tr
><tr id="gr_svn7768_2003"

><td id="2003"><a href="#2003">2003</a></td></tr
><tr id="gr_svn7768_2004"

><td id="2004"><a href="#2004">2004</a></td></tr
><tr id="gr_svn7768_2005"

><td id="2005"><a href="#2005">2005</a></td></tr
><tr id="gr_svn7768_2006"

><td id="2006"><a href="#2006">2006</a></td></tr
><tr id="gr_svn7768_2007"

><td id="2007"><a href="#2007">2007</a></td></tr
><tr id="gr_svn7768_2008"

><td id="2008"><a href="#2008">2008</a></td></tr
><tr id="gr_svn7768_2009"

><td id="2009"><a href="#2009">2009</a></td></tr
><tr id="gr_svn7768_2010"

><td id="2010"><a href="#2010">2010</a></td></tr
><tr id="gr_svn7768_2011"

><td id="2011"><a href="#2011">2011</a></td></tr
><tr id="gr_svn7768_2012"

><td id="2012"><a href="#2012">2012</a></td></tr
><tr id="gr_svn7768_2013"

><td id="2013"><a href="#2013">2013</a></td></tr
><tr id="gr_svn7768_2014"

><td id="2014"><a href="#2014">2014</a></td></tr
><tr id="gr_svn7768_2015"

><td id="2015"><a href="#2015">2015</a></td></tr
><tr id="gr_svn7768_2016"

><td id="2016"><a href="#2016">2016</a></td></tr
><tr id="gr_svn7768_2017"

><td id="2017"><a href="#2017">2017</a></td></tr
><tr id="gr_svn7768_2018"

><td id="2018"><a href="#2018">2018</a></td></tr
><tr id="gr_svn7768_2019"

><td id="2019"><a href="#2019">2019</a></td></tr
><tr id="gr_svn7768_2020"

><td id="2020"><a href="#2020">2020</a></td></tr
><tr id="gr_svn7768_2021"

><td id="2021"><a href="#2021">2021</a></td></tr
><tr id="gr_svn7768_2022"

><td id="2022"><a href="#2022">2022</a></td></tr
><tr id="gr_svn7768_2023"

><td id="2023"><a href="#2023">2023</a></td></tr
><tr id="gr_svn7768_2024"

><td id="2024"><a href="#2024">2024</a></td></tr
><tr id="gr_svn7768_2025"

><td id="2025"><a href="#2025">2025</a></td></tr
><tr id="gr_svn7768_2026"

><td id="2026"><a href="#2026">2026</a></td></tr
><tr id="gr_svn7768_2027"

><td id="2027"><a href="#2027">2027</a></td></tr
><tr id="gr_svn7768_2028"

><td id="2028"><a href="#2028">2028</a></td></tr
><tr id="gr_svn7768_2029"

><td id="2029"><a href="#2029">2029</a></td></tr
><tr id="gr_svn7768_2030"

><td id="2030"><a href="#2030">2030</a></td></tr
><tr id="gr_svn7768_2031"

><td id="2031"><a href="#2031">2031</a></td></tr
><tr id="gr_svn7768_2032"

><td id="2032"><a href="#2032">2032</a></td></tr
><tr id="gr_svn7768_2033"

><td id="2033"><a href="#2033">2033</a></td></tr
><tr id="gr_svn7768_2034"

><td id="2034"><a href="#2034">2034</a></td></tr
><tr id="gr_svn7768_2035"

><td id="2035"><a href="#2035">2035</a></td></tr
><tr id="gr_svn7768_2036"

><td id="2036"><a href="#2036">2036</a></td></tr
><tr id="gr_svn7768_2037"

><td id="2037"><a href="#2037">2037</a></td></tr
><tr id="gr_svn7768_2038"

><td id="2038"><a href="#2038">2038</a></td></tr
><tr id="gr_svn7768_2039"

><td id="2039"><a href="#2039">2039</a></td></tr
><tr id="gr_svn7768_2040"

><td id="2040"><a href="#2040">2040</a></td></tr
><tr id="gr_svn7768_2041"

><td id="2041"><a href="#2041">2041</a></td></tr
><tr id="gr_svn7768_2042"

><td id="2042"><a href="#2042">2042</a></td></tr
><tr id="gr_svn7768_2043"

><td id="2043"><a href="#2043">2043</a></td></tr
><tr id="gr_svn7768_2044"

><td id="2044"><a href="#2044">2044</a></td></tr
><tr id="gr_svn7768_2045"

><td id="2045"><a href="#2045">2045</a></td></tr
><tr id="gr_svn7768_2046"

><td id="2046"><a href="#2046">2046</a></td></tr
><tr id="gr_svn7768_2047"

><td id="2047"><a href="#2047">2047</a></td></tr
><tr id="gr_svn7768_2048"

><td id="2048"><a href="#2048">2048</a></td></tr
><tr id="gr_svn7768_2049"

><td id="2049"><a href="#2049">2049</a></td></tr
><tr id="gr_svn7768_2050"

><td id="2050"><a href="#2050">2050</a></td></tr
><tr id="gr_svn7768_2051"

><td id="2051"><a href="#2051">2051</a></td></tr
><tr id="gr_svn7768_2052"

><td id="2052"><a href="#2052">2052</a></td></tr
><tr id="gr_svn7768_2053"

><td id="2053"><a href="#2053">2053</a></td></tr
><tr id="gr_svn7768_2054"

><td id="2054"><a href="#2054">2054</a></td></tr
><tr id="gr_svn7768_2055"

><td id="2055"><a href="#2055">2055</a></td></tr
><tr id="gr_svn7768_2056"

><td id="2056"><a href="#2056">2056</a></td></tr
><tr id="gr_svn7768_2057"

><td id="2057"><a href="#2057">2057</a></td></tr
><tr id="gr_svn7768_2058"

><td id="2058"><a href="#2058">2058</a></td></tr
><tr id="gr_svn7768_2059"

><td id="2059"><a href="#2059">2059</a></td></tr
><tr id="gr_svn7768_2060"

><td id="2060"><a href="#2060">2060</a></td></tr
><tr id="gr_svn7768_2061"

><td id="2061"><a href="#2061">2061</a></td></tr
><tr id="gr_svn7768_2062"

><td id="2062"><a href="#2062">2062</a></td></tr
><tr id="gr_svn7768_2063"

><td id="2063"><a href="#2063">2063</a></td></tr
><tr id="gr_svn7768_2064"

><td id="2064"><a href="#2064">2064</a></td></tr
><tr id="gr_svn7768_2065"

><td id="2065"><a href="#2065">2065</a></td></tr
><tr id="gr_svn7768_2066"

><td id="2066"><a href="#2066">2066</a></td></tr
><tr id="gr_svn7768_2067"

><td id="2067"><a href="#2067">2067</a></td></tr
><tr id="gr_svn7768_2068"

><td id="2068"><a href="#2068">2068</a></td></tr
><tr id="gr_svn7768_2069"

><td id="2069"><a href="#2069">2069</a></td></tr
><tr id="gr_svn7768_2070"

><td id="2070"><a href="#2070">2070</a></td></tr
><tr id="gr_svn7768_2071"

><td id="2071"><a href="#2071">2071</a></td></tr
><tr id="gr_svn7768_2072"

><td id="2072"><a href="#2072">2072</a></td></tr
><tr id="gr_svn7768_2073"

><td id="2073"><a href="#2073">2073</a></td></tr
><tr id="gr_svn7768_2074"

><td id="2074"><a href="#2074">2074</a></td></tr
><tr id="gr_svn7768_2075"

><td id="2075"><a href="#2075">2075</a></td></tr
><tr id="gr_svn7768_2076"

><td id="2076"><a href="#2076">2076</a></td></tr
><tr id="gr_svn7768_2077"

><td id="2077"><a href="#2077">2077</a></td></tr
><tr id="gr_svn7768_2078"

><td id="2078"><a href="#2078">2078</a></td></tr
><tr id="gr_svn7768_2079"

><td id="2079"><a href="#2079">2079</a></td></tr
><tr id="gr_svn7768_2080"

><td id="2080"><a href="#2080">2080</a></td></tr
><tr id="gr_svn7768_2081"

><td id="2081"><a href="#2081">2081</a></td></tr
><tr id="gr_svn7768_2082"

><td id="2082"><a href="#2082">2082</a></td></tr
><tr id="gr_svn7768_2083"

><td id="2083"><a href="#2083">2083</a></td></tr
><tr id="gr_svn7768_2084"

><td id="2084"><a href="#2084">2084</a></td></tr
><tr id="gr_svn7768_2085"

><td id="2085"><a href="#2085">2085</a></td></tr
><tr id="gr_svn7768_2086"

><td id="2086"><a href="#2086">2086</a></td></tr
><tr id="gr_svn7768_2087"

><td id="2087"><a href="#2087">2087</a></td></tr
><tr id="gr_svn7768_2088"

><td id="2088"><a href="#2088">2088</a></td></tr
><tr id="gr_svn7768_2089"

><td id="2089"><a href="#2089">2089</a></td></tr
><tr id="gr_svn7768_2090"

><td id="2090"><a href="#2090">2090</a></td></tr
><tr id="gr_svn7768_2091"

><td id="2091"><a href="#2091">2091</a></td></tr
><tr id="gr_svn7768_2092"

><td id="2092"><a href="#2092">2092</a></td></tr
><tr id="gr_svn7768_2093"

><td id="2093"><a href="#2093">2093</a></td></tr
><tr id="gr_svn7768_2094"

><td id="2094"><a href="#2094">2094</a></td></tr
><tr id="gr_svn7768_2095"

><td id="2095"><a href="#2095">2095</a></td></tr
><tr id="gr_svn7768_2096"

><td id="2096"><a href="#2096">2096</a></td></tr
><tr id="gr_svn7768_2097"

><td id="2097"><a href="#2097">2097</a></td></tr
><tr id="gr_svn7768_2098"

><td id="2098"><a href="#2098">2098</a></td></tr
><tr id="gr_svn7768_2099"

><td id="2099"><a href="#2099">2099</a></td></tr
><tr id="gr_svn7768_2100"

><td id="2100"><a href="#2100">2100</a></td></tr
><tr id="gr_svn7768_2101"

><td id="2101"><a href="#2101">2101</a></td></tr
><tr id="gr_svn7768_2102"

><td id="2102"><a href="#2102">2102</a></td></tr
><tr id="gr_svn7768_2103"

><td id="2103"><a href="#2103">2103</a></td></tr
><tr id="gr_svn7768_2104"

><td id="2104"><a href="#2104">2104</a></td></tr
><tr id="gr_svn7768_2105"

><td id="2105"><a href="#2105">2105</a></td></tr
><tr id="gr_svn7768_2106"

><td id="2106"><a href="#2106">2106</a></td></tr
><tr id="gr_svn7768_2107"

><td id="2107"><a href="#2107">2107</a></td></tr
><tr id="gr_svn7768_2108"

><td id="2108"><a href="#2108">2108</a></td></tr
><tr id="gr_svn7768_2109"

><td id="2109"><a href="#2109">2109</a></td></tr
><tr id="gr_svn7768_2110"

><td id="2110"><a href="#2110">2110</a></td></tr
><tr id="gr_svn7768_2111"

><td id="2111"><a href="#2111">2111</a></td></tr
><tr id="gr_svn7768_2112"

><td id="2112"><a href="#2112">2112</a></td></tr
><tr id="gr_svn7768_2113"

><td id="2113"><a href="#2113">2113</a></td></tr
><tr id="gr_svn7768_2114"

><td id="2114"><a href="#2114">2114</a></td></tr
><tr id="gr_svn7768_2115"

><td id="2115"><a href="#2115">2115</a></td></tr
><tr id="gr_svn7768_2116"

><td id="2116"><a href="#2116">2116</a></td></tr
><tr id="gr_svn7768_2117"

><td id="2117"><a href="#2117">2117</a></td></tr
><tr id="gr_svn7768_2118"

><td id="2118"><a href="#2118">2118</a></td></tr
><tr id="gr_svn7768_2119"

><td id="2119"><a href="#2119">2119</a></td></tr
><tr id="gr_svn7768_2120"

><td id="2120"><a href="#2120">2120</a></td></tr
><tr id="gr_svn7768_2121"

><td id="2121"><a href="#2121">2121</a></td></tr
><tr id="gr_svn7768_2122"

><td id="2122"><a href="#2122">2122</a></td></tr
><tr id="gr_svn7768_2123"

><td id="2123"><a href="#2123">2123</a></td></tr
><tr id="gr_svn7768_2124"

><td id="2124"><a href="#2124">2124</a></td></tr
><tr id="gr_svn7768_2125"

><td id="2125"><a href="#2125">2125</a></td></tr
><tr id="gr_svn7768_2126"

><td id="2126"><a href="#2126">2126</a></td></tr
><tr id="gr_svn7768_2127"

><td id="2127"><a href="#2127">2127</a></td></tr
><tr id="gr_svn7768_2128"

><td id="2128"><a href="#2128">2128</a></td></tr
><tr id="gr_svn7768_2129"

><td id="2129"><a href="#2129">2129</a></td></tr
><tr id="gr_svn7768_2130"

><td id="2130"><a href="#2130">2130</a></td></tr
><tr id="gr_svn7768_2131"

><td id="2131"><a href="#2131">2131</a></td></tr
><tr id="gr_svn7768_2132"

><td id="2132"><a href="#2132">2132</a></td></tr
><tr id="gr_svn7768_2133"

><td id="2133"><a href="#2133">2133</a></td></tr
><tr id="gr_svn7768_2134"

><td id="2134"><a href="#2134">2134</a></td></tr
><tr id="gr_svn7768_2135"

><td id="2135"><a href="#2135">2135</a></td></tr
><tr id="gr_svn7768_2136"

><td id="2136"><a href="#2136">2136</a></td></tr
><tr id="gr_svn7768_2137"

><td id="2137"><a href="#2137">2137</a></td></tr
><tr id="gr_svn7768_2138"

><td id="2138"><a href="#2138">2138</a></td></tr
><tr id="gr_svn7768_2139"

><td id="2139"><a href="#2139">2139</a></td></tr
><tr id="gr_svn7768_2140"

><td id="2140"><a href="#2140">2140</a></td></tr
><tr id="gr_svn7768_2141"

><td id="2141"><a href="#2141">2141</a></td></tr
><tr id="gr_svn7768_2142"

><td id="2142"><a href="#2142">2142</a></td></tr
><tr id="gr_svn7768_2143"

><td id="2143"><a href="#2143">2143</a></td></tr
><tr id="gr_svn7768_2144"

><td id="2144"><a href="#2144">2144</a></td></tr
><tr id="gr_svn7768_2145"

><td id="2145"><a href="#2145">2145</a></td></tr
><tr id="gr_svn7768_2146"

><td id="2146"><a href="#2146">2146</a></td></tr
><tr id="gr_svn7768_2147"

><td id="2147"><a href="#2147">2147</a></td></tr
><tr id="gr_svn7768_2148"

><td id="2148"><a href="#2148">2148</a></td></tr
><tr id="gr_svn7768_2149"

><td id="2149"><a href="#2149">2149</a></td></tr
><tr id="gr_svn7768_2150"

><td id="2150"><a href="#2150">2150</a></td></tr
><tr id="gr_svn7768_2151"

><td id="2151"><a href="#2151">2151</a></td></tr
><tr id="gr_svn7768_2152"

><td id="2152"><a href="#2152">2152</a></td></tr
><tr id="gr_svn7768_2153"

><td id="2153"><a href="#2153">2153</a></td></tr
><tr id="gr_svn7768_2154"

><td id="2154"><a href="#2154">2154</a></td></tr
><tr id="gr_svn7768_2155"

><td id="2155"><a href="#2155">2155</a></td></tr
><tr id="gr_svn7768_2156"

><td id="2156"><a href="#2156">2156</a></td></tr
><tr id="gr_svn7768_2157"

><td id="2157"><a href="#2157">2157</a></td></tr
><tr id="gr_svn7768_2158"

><td id="2158"><a href="#2158">2158</a></td></tr
><tr id="gr_svn7768_2159"

><td id="2159"><a href="#2159">2159</a></td></tr
><tr id="gr_svn7768_2160"

><td id="2160"><a href="#2160">2160</a></td></tr
><tr id="gr_svn7768_2161"

><td id="2161"><a href="#2161">2161</a></td></tr
><tr id="gr_svn7768_2162"

><td id="2162"><a href="#2162">2162</a></td></tr
><tr id="gr_svn7768_2163"

><td id="2163"><a href="#2163">2163</a></td></tr
><tr id="gr_svn7768_2164"

><td id="2164"><a href="#2164">2164</a></td></tr
><tr id="gr_svn7768_2165"

><td id="2165"><a href="#2165">2165</a></td></tr
><tr id="gr_svn7768_2166"

><td id="2166"><a href="#2166">2166</a></td></tr
><tr id="gr_svn7768_2167"

><td id="2167"><a href="#2167">2167</a></td></tr
><tr id="gr_svn7768_2168"

><td id="2168"><a href="#2168">2168</a></td></tr
><tr id="gr_svn7768_2169"

><td id="2169"><a href="#2169">2169</a></td></tr
><tr id="gr_svn7768_2170"

><td id="2170"><a href="#2170">2170</a></td></tr
><tr id="gr_svn7768_2171"

><td id="2171"><a href="#2171">2171</a></td></tr
><tr id="gr_svn7768_2172"

><td id="2172"><a href="#2172">2172</a></td></tr
><tr id="gr_svn7768_2173"

><td id="2173"><a href="#2173">2173</a></td></tr
><tr id="gr_svn7768_2174"

><td id="2174"><a href="#2174">2174</a></td></tr
><tr id="gr_svn7768_2175"

><td id="2175"><a href="#2175">2175</a></td></tr
><tr id="gr_svn7768_2176"

><td id="2176"><a href="#2176">2176</a></td></tr
><tr id="gr_svn7768_2177"

><td id="2177"><a href="#2177">2177</a></td></tr
><tr id="gr_svn7768_2178"

><td id="2178"><a href="#2178">2178</a></td></tr
><tr id="gr_svn7768_2179"

><td id="2179"><a href="#2179">2179</a></td></tr
><tr id="gr_svn7768_2180"

><td id="2180"><a href="#2180">2180</a></td></tr
><tr id="gr_svn7768_2181"

><td id="2181"><a href="#2181">2181</a></td></tr
><tr id="gr_svn7768_2182"

><td id="2182"><a href="#2182">2182</a></td></tr
><tr id="gr_svn7768_2183"

><td id="2183"><a href="#2183">2183</a></td></tr
><tr id="gr_svn7768_2184"

><td id="2184"><a href="#2184">2184</a></td></tr
><tr id="gr_svn7768_2185"

><td id="2185"><a href="#2185">2185</a></td></tr
><tr id="gr_svn7768_2186"

><td id="2186"><a href="#2186">2186</a></td></tr
><tr id="gr_svn7768_2187"

><td id="2187"><a href="#2187">2187</a></td></tr
><tr id="gr_svn7768_2188"

><td id="2188"><a href="#2188">2188</a></td></tr
><tr id="gr_svn7768_2189"

><td id="2189"><a href="#2189">2189</a></td></tr
><tr id="gr_svn7768_2190"

><td id="2190"><a href="#2190">2190</a></td></tr
><tr id="gr_svn7768_2191"

><td id="2191"><a href="#2191">2191</a></td></tr
><tr id="gr_svn7768_2192"

><td id="2192"><a href="#2192">2192</a></td></tr
><tr id="gr_svn7768_2193"

><td id="2193"><a href="#2193">2193</a></td></tr
><tr id="gr_svn7768_2194"

><td id="2194"><a href="#2194">2194</a></td></tr
><tr id="gr_svn7768_2195"

><td id="2195"><a href="#2195">2195</a></td></tr
><tr id="gr_svn7768_2196"

><td id="2196"><a href="#2196">2196</a></td></tr
><tr id="gr_svn7768_2197"

><td id="2197"><a href="#2197">2197</a></td></tr
><tr id="gr_svn7768_2198"

><td id="2198"><a href="#2198">2198</a></td></tr
><tr id="gr_svn7768_2199"

><td id="2199"><a href="#2199">2199</a></td></tr
><tr id="gr_svn7768_2200"

><td id="2200"><a href="#2200">2200</a></td></tr
><tr id="gr_svn7768_2201"

><td id="2201"><a href="#2201">2201</a></td></tr
><tr id="gr_svn7768_2202"

><td id="2202"><a href="#2202">2202</a></td></tr
><tr id="gr_svn7768_2203"

><td id="2203"><a href="#2203">2203</a></td></tr
><tr id="gr_svn7768_2204"

><td id="2204"><a href="#2204">2204</a></td></tr
><tr id="gr_svn7768_2205"

><td id="2205"><a href="#2205">2205</a></td></tr
><tr id="gr_svn7768_2206"

><td id="2206"><a href="#2206">2206</a></td></tr
><tr id="gr_svn7768_2207"

><td id="2207"><a href="#2207">2207</a></td></tr
><tr id="gr_svn7768_2208"

><td id="2208"><a href="#2208">2208</a></td></tr
><tr id="gr_svn7768_2209"

><td id="2209"><a href="#2209">2209</a></td></tr
><tr id="gr_svn7768_2210"

><td id="2210"><a href="#2210">2210</a></td></tr
><tr id="gr_svn7768_2211"

><td id="2211"><a href="#2211">2211</a></td></tr
><tr id="gr_svn7768_2212"

><td id="2212"><a href="#2212">2212</a></td></tr
><tr id="gr_svn7768_2213"

><td id="2213"><a href="#2213">2213</a></td></tr
><tr id="gr_svn7768_2214"

><td id="2214"><a href="#2214">2214</a></td></tr
><tr id="gr_svn7768_2215"

><td id="2215"><a href="#2215">2215</a></td></tr
><tr id="gr_svn7768_2216"

><td id="2216"><a href="#2216">2216</a></td></tr
><tr id="gr_svn7768_2217"

><td id="2217"><a href="#2217">2217</a></td></tr
><tr id="gr_svn7768_2218"

><td id="2218"><a href="#2218">2218</a></td></tr
><tr id="gr_svn7768_2219"

><td id="2219"><a href="#2219">2219</a></td></tr
><tr id="gr_svn7768_2220"

><td id="2220"><a href="#2220">2220</a></td></tr
><tr id="gr_svn7768_2221"

><td id="2221"><a href="#2221">2221</a></td></tr
><tr id="gr_svn7768_2222"

><td id="2222"><a href="#2222">2222</a></td></tr
><tr id="gr_svn7768_2223"

><td id="2223"><a href="#2223">2223</a></td></tr
><tr id="gr_svn7768_2224"

><td id="2224"><a href="#2224">2224</a></td></tr
><tr id="gr_svn7768_2225"

><td id="2225"><a href="#2225">2225</a></td></tr
><tr id="gr_svn7768_2226"

><td id="2226"><a href="#2226">2226</a></td></tr
><tr id="gr_svn7768_2227"

><td id="2227"><a href="#2227">2227</a></td></tr
><tr id="gr_svn7768_2228"

><td id="2228"><a href="#2228">2228</a></td></tr
><tr id="gr_svn7768_2229"

><td id="2229"><a href="#2229">2229</a></td></tr
><tr id="gr_svn7768_2230"

><td id="2230"><a href="#2230">2230</a></td></tr
><tr id="gr_svn7768_2231"

><td id="2231"><a href="#2231">2231</a></td></tr
><tr id="gr_svn7768_2232"

><td id="2232"><a href="#2232">2232</a></td></tr
><tr id="gr_svn7768_2233"

><td id="2233"><a href="#2233">2233</a></td></tr
><tr id="gr_svn7768_2234"

><td id="2234"><a href="#2234">2234</a></td></tr
><tr id="gr_svn7768_2235"

><td id="2235"><a href="#2235">2235</a></td></tr
><tr id="gr_svn7768_2236"

><td id="2236"><a href="#2236">2236</a></td></tr
><tr id="gr_svn7768_2237"

><td id="2237"><a href="#2237">2237</a></td></tr
><tr id="gr_svn7768_2238"

><td id="2238"><a href="#2238">2238</a></td></tr
><tr id="gr_svn7768_2239"

><td id="2239"><a href="#2239">2239</a></td></tr
><tr id="gr_svn7768_2240"

><td id="2240"><a href="#2240">2240</a></td></tr
><tr id="gr_svn7768_2241"

><td id="2241"><a href="#2241">2241</a></td></tr
><tr id="gr_svn7768_2242"

><td id="2242"><a href="#2242">2242</a></td></tr
><tr id="gr_svn7768_2243"

><td id="2243"><a href="#2243">2243</a></td></tr
><tr id="gr_svn7768_2244"

><td id="2244"><a href="#2244">2244</a></td></tr
><tr id="gr_svn7768_2245"

><td id="2245"><a href="#2245">2245</a></td></tr
><tr id="gr_svn7768_2246"

><td id="2246"><a href="#2246">2246</a></td></tr
><tr id="gr_svn7768_2247"

><td id="2247"><a href="#2247">2247</a></td></tr
><tr id="gr_svn7768_2248"

><td id="2248"><a href="#2248">2248</a></td></tr
><tr id="gr_svn7768_2249"

><td id="2249"><a href="#2249">2249</a></td></tr
><tr id="gr_svn7768_2250"

><td id="2250"><a href="#2250">2250</a></td></tr
><tr id="gr_svn7768_2251"

><td id="2251"><a href="#2251">2251</a></td></tr
><tr id="gr_svn7768_2252"

><td id="2252"><a href="#2252">2252</a></td></tr
><tr id="gr_svn7768_2253"

><td id="2253"><a href="#2253">2253</a></td></tr
><tr id="gr_svn7768_2254"

><td id="2254"><a href="#2254">2254</a></td></tr
><tr id="gr_svn7768_2255"

><td id="2255"><a href="#2255">2255</a></td></tr
><tr id="gr_svn7768_2256"

><td id="2256"><a href="#2256">2256</a></td></tr
><tr id="gr_svn7768_2257"

><td id="2257"><a href="#2257">2257</a></td></tr
><tr id="gr_svn7768_2258"

><td id="2258"><a href="#2258">2258</a></td></tr
><tr id="gr_svn7768_2259"

><td id="2259"><a href="#2259">2259</a></td></tr
><tr id="gr_svn7768_2260"

><td id="2260"><a href="#2260">2260</a></td></tr
><tr id="gr_svn7768_2261"

><td id="2261"><a href="#2261">2261</a></td></tr
><tr id="gr_svn7768_2262"

><td id="2262"><a href="#2262">2262</a></td></tr
><tr id="gr_svn7768_2263"

><td id="2263"><a href="#2263">2263</a></td></tr
><tr id="gr_svn7768_2264"

><td id="2264"><a href="#2264">2264</a></td></tr
><tr id="gr_svn7768_2265"

><td id="2265"><a href="#2265">2265</a></td></tr
><tr id="gr_svn7768_2266"

><td id="2266"><a href="#2266">2266</a></td></tr
><tr id="gr_svn7768_2267"

><td id="2267"><a href="#2267">2267</a></td></tr
><tr id="gr_svn7768_2268"

><td id="2268"><a href="#2268">2268</a></td></tr
><tr id="gr_svn7768_2269"

><td id="2269"><a href="#2269">2269</a></td></tr
><tr id="gr_svn7768_2270"

><td id="2270"><a href="#2270">2270</a></td></tr
><tr id="gr_svn7768_2271"

><td id="2271"><a href="#2271">2271</a></td></tr
><tr id="gr_svn7768_2272"

><td id="2272"><a href="#2272">2272</a></td></tr
><tr id="gr_svn7768_2273"

><td id="2273"><a href="#2273">2273</a></td></tr
><tr id="gr_svn7768_2274"

><td id="2274"><a href="#2274">2274</a></td></tr
><tr id="gr_svn7768_2275"

><td id="2275"><a href="#2275">2275</a></td></tr
><tr id="gr_svn7768_2276"

><td id="2276"><a href="#2276">2276</a></td></tr
><tr id="gr_svn7768_2277"

><td id="2277"><a href="#2277">2277</a></td></tr
><tr id="gr_svn7768_2278"

><td id="2278"><a href="#2278">2278</a></td></tr
><tr id="gr_svn7768_2279"

><td id="2279"><a href="#2279">2279</a></td></tr
><tr id="gr_svn7768_2280"

><td id="2280"><a href="#2280">2280</a></td></tr
><tr id="gr_svn7768_2281"

><td id="2281"><a href="#2281">2281</a></td></tr
><tr id="gr_svn7768_2282"

><td id="2282"><a href="#2282">2282</a></td></tr
><tr id="gr_svn7768_2283"

><td id="2283"><a href="#2283">2283</a></td></tr
><tr id="gr_svn7768_2284"

><td id="2284"><a href="#2284">2284</a></td></tr
><tr id="gr_svn7768_2285"

><td id="2285"><a href="#2285">2285</a></td></tr
><tr id="gr_svn7768_2286"

><td id="2286"><a href="#2286">2286</a></td></tr
><tr id="gr_svn7768_2287"

><td id="2287"><a href="#2287">2287</a></td></tr
><tr id="gr_svn7768_2288"

><td id="2288"><a href="#2288">2288</a></td></tr
><tr id="gr_svn7768_2289"

><td id="2289"><a href="#2289">2289</a></td></tr
><tr id="gr_svn7768_2290"

><td id="2290"><a href="#2290">2290</a></td></tr
><tr id="gr_svn7768_2291"

><td id="2291"><a href="#2291">2291</a></td></tr
><tr id="gr_svn7768_2292"

><td id="2292"><a href="#2292">2292</a></td></tr
><tr id="gr_svn7768_2293"

><td id="2293"><a href="#2293">2293</a></td></tr
><tr id="gr_svn7768_2294"

><td id="2294"><a href="#2294">2294</a></td></tr
><tr id="gr_svn7768_2295"

><td id="2295"><a href="#2295">2295</a></td></tr
><tr id="gr_svn7768_2296"

><td id="2296"><a href="#2296">2296</a></td></tr
><tr id="gr_svn7768_2297"

><td id="2297"><a href="#2297">2297</a></td></tr
><tr id="gr_svn7768_2298"

><td id="2298"><a href="#2298">2298</a></td></tr
><tr id="gr_svn7768_2299"

><td id="2299"><a href="#2299">2299</a></td></tr
><tr id="gr_svn7768_2300"

><td id="2300"><a href="#2300">2300</a></td></tr
><tr id="gr_svn7768_2301"

><td id="2301"><a href="#2301">2301</a></td></tr
><tr id="gr_svn7768_2302"

><td id="2302"><a href="#2302">2302</a></td></tr
><tr id="gr_svn7768_2303"

><td id="2303"><a href="#2303">2303</a></td></tr
><tr id="gr_svn7768_2304"

><td id="2304"><a href="#2304">2304</a></td></tr
><tr id="gr_svn7768_2305"

><td id="2305"><a href="#2305">2305</a></td></tr
><tr id="gr_svn7768_2306"

><td id="2306"><a href="#2306">2306</a></td></tr
><tr id="gr_svn7768_2307"

><td id="2307"><a href="#2307">2307</a></td></tr
><tr id="gr_svn7768_2308"

><td id="2308"><a href="#2308">2308</a></td></tr
><tr id="gr_svn7768_2309"

><td id="2309"><a href="#2309">2309</a></td></tr
><tr id="gr_svn7768_2310"

><td id="2310"><a href="#2310">2310</a></td></tr
><tr id="gr_svn7768_2311"

><td id="2311"><a href="#2311">2311</a></td></tr
><tr id="gr_svn7768_2312"

><td id="2312"><a href="#2312">2312</a></td></tr
><tr id="gr_svn7768_2313"

><td id="2313"><a href="#2313">2313</a></td></tr
><tr id="gr_svn7768_2314"

><td id="2314"><a href="#2314">2314</a></td></tr
><tr id="gr_svn7768_2315"

><td id="2315"><a href="#2315">2315</a></td></tr
><tr id="gr_svn7768_2316"

><td id="2316"><a href="#2316">2316</a></td></tr
><tr id="gr_svn7768_2317"

><td id="2317"><a href="#2317">2317</a></td></tr
><tr id="gr_svn7768_2318"

><td id="2318"><a href="#2318">2318</a></td></tr
><tr id="gr_svn7768_2319"

><td id="2319"><a href="#2319">2319</a></td></tr
><tr id="gr_svn7768_2320"

><td id="2320"><a href="#2320">2320</a></td></tr
><tr id="gr_svn7768_2321"

><td id="2321"><a href="#2321">2321</a></td></tr
><tr id="gr_svn7768_2322"

><td id="2322"><a href="#2322">2322</a></td></tr
><tr id="gr_svn7768_2323"

><td id="2323"><a href="#2323">2323</a></td></tr
><tr id="gr_svn7768_2324"

><td id="2324"><a href="#2324">2324</a></td></tr
><tr id="gr_svn7768_2325"

><td id="2325"><a href="#2325">2325</a></td></tr
><tr id="gr_svn7768_2326"

><td id="2326"><a href="#2326">2326</a></td></tr
><tr id="gr_svn7768_2327"

><td id="2327"><a href="#2327">2327</a></td></tr
><tr id="gr_svn7768_2328"

><td id="2328"><a href="#2328">2328</a></td></tr
><tr id="gr_svn7768_2329"

><td id="2329"><a href="#2329">2329</a></td></tr
><tr id="gr_svn7768_2330"

><td id="2330"><a href="#2330">2330</a></td></tr
><tr id="gr_svn7768_2331"

><td id="2331"><a href="#2331">2331</a></td></tr
><tr id="gr_svn7768_2332"

><td id="2332"><a href="#2332">2332</a></td></tr
><tr id="gr_svn7768_2333"

><td id="2333"><a href="#2333">2333</a></td></tr
><tr id="gr_svn7768_2334"

><td id="2334"><a href="#2334">2334</a></td></tr
><tr id="gr_svn7768_2335"

><td id="2335"><a href="#2335">2335</a></td></tr
><tr id="gr_svn7768_2336"

><td id="2336"><a href="#2336">2336</a></td></tr
><tr id="gr_svn7768_2337"

><td id="2337"><a href="#2337">2337</a></td></tr
><tr id="gr_svn7768_2338"

><td id="2338"><a href="#2338">2338</a></td></tr
><tr id="gr_svn7768_2339"

><td id="2339"><a href="#2339">2339</a></td></tr
><tr id="gr_svn7768_2340"

><td id="2340"><a href="#2340">2340</a></td></tr
><tr id="gr_svn7768_2341"

><td id="2341"><a href="#2341">2341</a></td></tr
><tr id="gr_svn7768_2342"

><td id="2342"><a href="#2342">2342</a></td></tr
><tr id="gr_svn7768_2343"

><td id="2343"><a href="#2343">2343</a></td></tr
><tr id="gr_svn7768_2344"

><td id="2344"><a href="#2344">2344</a></td></tr
><tr id="gr_svn7768_2345"

><td id="2345"><a href="#2345">2345</a></td></tr
><tr id="gr_svn7768_2346"

><td id="2346"><a href="#2346">2346</a></td></tr
><tr id="gr_svn7768_2347"

><td id="2347"><a href="#2347">2347</a></td></tr
><tr id="gr_svn7768_2348"

><td id="2348"><a href="#2348">2348</a></td></tr
><tr id="gr_svn7768_2349"

><td id="2349"><a href="#2349">2349</a></td></tr
><tr id="gr_svn7768_2350"

><td id="2350"><a href="#2350">2350</a></td></tr
><tr id="gr_svn7768_2351"

><td id="2351"><a href="#2351">2351</a></td></tr
><tr id="gr_svn7768_2352"

><td id="2352"><a href="#2352">2352</a></td></tr
><tr id="gr_svn7768_2353"

><td id="2353"><a href="#2353">2353</a></td></tr
><tr id="gr_svn7768_2354"

><td id="2354"><a href="#2354">2354</a></td></tr
><tr id="gr_svn7768_2355"

><td id="2355"><a href="#2355">2355</a></td></tr
><tr id="gr_svn7768_2356"

><td id="2356"><a href="#2356">2356</a></td></tr
><tr id="gr_svn7768_2357"

><td id="2357"><a href="#2357">2357</a></td></tr
><tr id="gr_svn7768_2358"

><td id="2358"><a href="#2358">2358</a></td></tr
><tr id="gr_svn7768_2359"

><td id="2359"><a href="#2359">2359</a></td></tr
><tr id="gr_svn7768_2360"

><td id="2360"><a href="#2360">2360</a></td></tr
><tr id="gr_svn7768_2361"

><td id="2361"><a href="#2361">2361</a></td></tr
><tr id="gr_svn7768_2362"

><td id="2362"><a href="#2362">2362</a></td></tr
><tr id="gr_svn7768_2363"

><td id="2363"><a href="#2363">2363</a></td></tr
><tr id="gr_svn7768_2364"

><td id="2364"><a href="#2364">2364</a></td></tr
><tr id="gr_svn7768_2365"

><td id="2365"><a href="#2365">2365</a></td></tr
><tr id="gr_svn7768_2366"

><td id="2366"><a href="#2366">2366</a></td></tr
><tr id="gr_svn7768_2367"

><td id="2367"><a href="#2367">2367</a></td></tr
><tr id="gr_svn7768_2368"

><td id="2368"><a href="#2368">2368</a></td></tr
><tr id="gr_svn7768_2369"

><td id="2369"><a href="#2369">2369</a></td></tr
><tr id="gr_svn7768_2370"

><td id="2370"><a href="#2370">2370</a></td></tr
><tr id="gr_svn7768_2371"

><td id="2371"><a href="#2371">2371</a></td></tr
><tr id="gr_svn7768_2372"

><td id="2372"><a href="#2372">2372</a></td></tr
><tr id="gr_svn7768_2373"

><td id="2373"><a href="#2373">2373</a></td></tr
><tr id="gr_svn7768_2374"

><td id="2374"><a href="#2374">2374</a></td></tr
><tr id="gr_svn7768_2375"

><td id="2375"><a href="#2375">2375</a></td></tr
><tr id="gr_svn7768_2376"

><td id="2376"><a href="#2376">2376</a></td></tr
><tr id="gr_svn7768_2377"

><td id="2377"><a href="#2377">2377</a></td></tr
><tr id="gr_svn7768_2378"

><td id="2378"><a href="#2378">2378</a></td></tr
><tr id="gr_svn7768_2379"

><td id="2379"><a href="#2379">2379</a></td></tr
><tr id="gr_svn7768_2380"

><td id="2380"><a href="#2380">2380</a></td></tr
><tr id="gr_svn7768_2381"

><td id="2381"><a href="#2381">2381</a></td></tr
><tr id="gr_svn7768_2382"

><td id="2382"><a href="#2382">2382</a></td></tr
><tr id="gr_svn7768_2383"

><td id="2383"><a href="#2383">2383</a></td></tr
><tr id="gr_svn7768_2384"

><td id="2384"><a href="#2384">2384</a></td></tr
><tr id="gr_svn7768_2385"

><td id="2385"><a href="#2385">2385</a></td></tr
><tr id="gr_svn7768_2386"

><td id="2386"><a href="#2386">2386</a></td></tr
><tr id="gr_svn7768_2387"

><td id="2387"><a href="#2387">2387</a></td></tr
><tr id="gr_svn7768_2388"

><td id="2388"><a href="#2388">2388</a></td></tr
><tr id="gr_svn7768_2389"

><td id="2389"><a href="#2389">2389</a></td></tr
><tr id="gr_svn7768_2390"

><td id="2390"><a href="#2390">2390</a></td></tr
><tr id="gr_svn7768_2391"

><td id="2391"><a href="#2391">2391</a></td></tr
><tr id="gr_svn7768_2392"

><td id="2392"><a href="#2392">2392</a></td></tr
><tr id="gr_svn7768_2393"

><td id="2393"><a href="#2393">2393</a></td></tr
><tr id="gr_svn7768_2394"

><td id="2394"><a href="#2394">2394</a></td></tr
><tr id="gr_svn7768_2395"

><td id="2395"><a href="#2395">2395</a></td></tr
><tr id="gr_svn7768_2396"

><td id="2396"><a href="#2396">2396</a></td></tr
><tr id="gr_svn7768_2397"

><td id="2397"><a href="#2397">2397</a></td></tr
><tr id="gr_svn7768_2398"

><td id="2398"><a href="#2398">2398</a></td></tr
><tr id="gr_svn7768_2399"

><td id="2399"><a href="#2399">2399</a></td></tr
><tr id="gr_svn7768_2400"

><td id="2400"><a href="#2400">2400</a></td></tr
><tr id="gr_svn7768_2401"

><td id="2401"><a href="#2401">2401</a></td></tr
><tr id="gr_svn7768_2402"

><td id="2402"><a href="#2402">2402</a></td></tr
><tr id="gr_svn7768_2403"

><td id="2403"><a href="#2403">2403</a></td></tr
><tr id="gr_svn7768_2404"

><td id="2404"><a href="#2404">2404</a></td></tr
><tr id="gr_svn7768_2405"

><td id="2405"><a href="#2405">2405</a></td></tr
><tr id="gr_svn7768_2406"

><td id="2406"><a href="#2406">2406</a></td></tr
><tr id="gr_svn7768_2407"

><td id="2407"><a href="#2407">2407</a></td></tr
><tr id="gr_svn7768_2408"

><td id="2408"><a href="#2408">2408</a></td></tr
><tr id="gr_svn7768_2409"

><td id="2409"><a href="#2409">2409</a></td></tr
><tr id="gr_svn7768_2410"

><td id="2410"><a href="#2410">2410</a></td></tr
><tr id="gr_svn7768_2411"

><td id="2411"><a href="#2411">2411</a></td></tr
><tr id="gr_svn7768_2412"

><td id="2412"><a href="#2412">2412</a></td></tr
><tr id="gr_svn7768_2413"

><td id="2413"><a href="#2413">2413</a></td></tr
><tr id="gr_svn7768_2414"

><td id="2414"><a href="#2414">2414</a></td></tr
><tr id="gr_svn7768_2415"

><td id="2415"><a href="#2415">2415</a></td></tr
><tr id="gr_svn7768_2416"

><td id="2416"><a href="#2416">2416</a></td></tr
><tr id="gr_svn7768_2417"

><td id="2417"><a href="#2417">2417</a></td></tr
><tr id="gr_svn7768_2418"

><td id="2418"><a href="#2418">2418</a></td></tr
><tr id="gr_svn7768_2419"

><td id="2419"><a href="#2419">2419</a></td></tr
><tr id="gr_svn7768_2420"

><td id="2420"><a href="#2420">2420</a></td></tr
><tr id="gr_svn7768_2421"

><td id="2421"><a href="#2421">2421</a></td></tr
><tr id="gr_svn7768_2422"

><td id="2422"><a href="#2422">2422</a></td></tr
><tr id="gr_svn7768_2423"

><td id="2423"><a href="#2423">2423</a></td></tr
><tr id="gr_svn7768_2424"

><td id="2424"><a href="#2424">2424</a></td></tr
><tr id="gr_svn7768_2425"

><td id="2425"><a href="#2425">2425</a></td></tr
><tr id="gr_svn7768_2426"

><td id="2426"><a href="#2426">2426</a></td></tr
><tr id="gr_svn7768_2427"

><td id="2427"><a href="#2427">2427</a></td></tr
><tr id="gr_svn7768_2428"

><td id="2428"><a href="#2428">2428</a></td></tr
><tr id="gr_svn7768_2429"

><td id="2429"><a href="#2429">2429</a></td></tr
><tr id="gr_svn7768_2430"

><td id="2430"><a href="#2430">2430</a></td></tr
><tr id="gr_svn7768_2431"

><td id="2431"><a href="#2431">2431</a></td></tr
><tr id="gr_svn7768_2432"

><td id="2432"><a href="#2432">2432</a></td></tr
><tr id="gr_svn7768_2433"

><td id="2433"><a href="#2433">2433</a></td></tr
><tr id="gr_svn7768_2434"

><td id="2434"><a href="#2434">2434</a></td></tr
><tr id="gr_svn7768_2435"

><td id="2435"><a href="#2435">2435</a></td></tr
><tr id="gr_svn7768_2436"

><td id="2436"><a href="#2436">2436</a></td></tr
><tr id="gr_svn7768_2437"

><td id="2437"><a href="#2437">2437</a></td></tr
><tr id="gr_svn7768_2438"

><td id="2438"><a href="#2438">2438</a></td></tr
><tr id="gr_svn7768_2439"

><td id="2439"><a href="#2439">2439</a></td></tr
><tr id="gr_svn7768_2440"

><td id="2440"><a href="#2440">2440</a></td></tr
><tr id="gr_svn7768_2441"

><td id="2441"><a href="#2441">2441</a></td></tr
><tr id="gr_svn7768_2442"

><td id="2442"><a href="#2442">2442</a></td></tr
><tr id="gr_svn7768_2443"

><td id="2443"><a href="#2443">2443</a></td></tr
><tr id="gr_svn7768_2444"

><td id="2444"><a href="#2444">2444</a></td></tr
><tr id="gr_svn7768_2445"

><td id="2445"><a href="#2445">2445</a></td></tr
><tr id="gr_svn7768_2446"

><td id="2446"><a href="#2446">2446</a></td></tr
><tr id="gr_svn7768_2447"

><td id="2447"><a href="#2447">2447</a></td></tr
><tr id="gr_svn7768_2448"

><td id="2448"><a href="#2448">2448</a></td></tr
><tr id="gr_svn7768_2449"

><td id="2449"><a href="#2449">2449</a></td></tr
><tr id="gr_svn7768_2450"

><td id="2450"><a href="#2450">2450</a></td></tr
><tr id="gr_svn7768_2451"

><td id="2451"><a href="#2451">2451</a></td></tr
><tr id="gr_svn7768_2452"

><td id="2452"><a href="#2452">2452</a></td></tr
><tr id="gr_svn7768_2453"

><td id="2453"><a href="#2453">2453</a></td></tr
><tr id="gr_svn7768_2454"

><td id="2454"><a href="#2454">2454</a></td></tr
><tr id="gr_svn7768_2455"

><td id="2455"><a href="#2455">2455</a></td></tr
><tr id="gr_svn7768_2456"

><td id="2456"><a href="#2456">2456</a></td></tr
><tr id="gr_svn7768_2457"

><td id="2457"><a href="#2457">2457</a></td></tr
><tr id="gr_svn7768_2458"

><td id="2458"><a href="#2458">2458</a></td></tr
><tr id="gr_svn7768_2459"

><td id="2459"><a href="#2459">2459</a></td></tr
><tr id="gr_svn7768_2460"

><td id="2460"><a href="#2460">2460</a></td></tr
><tr id="gr_svn7768_2461"

><td id="2461"><a href="#2461">2461</a></td></tr
><tr id="gr_svn7768_2462"

><td id="2462"><a href="#2462">2462</a></td></tr
><tr id="gr_svn7768_2463"

><td id="2463"><a href="#2463">2463</a></td></tr
><tr id="gr_svn7768_2464"

><td id="2464"><a href="#2464">2464</a></td></tr
><tr id="gr_svn7768_2465"

><td id="2465"><a href="#2465">2465</a></td></tr
><tr id="gr_svn7768_2466"

><td id="2466"><a href="#2466">2466</a></td></tr
><tr id="gr_svn7768_2467"

><td id="2467"><a href="#2467">2467</a></td></tr
><tr id="gr_svn7768_2468"

><td id="2468"><a href="#2468">2468</a></td></tr
><tr id="gr_svn7768_2469"

><td id="2469"><a href="#2469">2469</a></td></tr
><tr id="gr_svn7768_2470"

><td id="2470"><a href="#2470">2470</a></td></tr
><tr id="gr_svn7768_2471"

><td id="2471"><a href="#2471">2471</a></td></tr
><tr id="gr_svn7768_2472"

><td id="2472"><a href="#2472">2472</a></td></tr
><tr id="gr_svn7768_2473"

><td id="2473"><a href="#2473">2473</a></td></tr
><tr id="gr_svn7768_2474"

><td id="2474"><a href="#2474">2474</a></td></tr
><tr id="gr_svn7768_2475"

><td id="2475"><a href="#2475">2475</a></td></tr
><tr id="gr_svn7768_2476"

><td id="2476"><a href="#2476">2476</a></td></tr
><tr id="gr_svn7768_2477"

><td id="2477"><a href="#2477">2477</a></td></tr
><tr id="gr_svn7768_2478"

><td id="2478"><a href="#2478">2478</a></td></tr
><tr id="gr_svn7768_2479"

><td id="2479"><a href="#2479">2479</a></td></tr
><tr id="gr_svn7768_2480"

><td id="2480"><a href="#2480">2480</a></td></tr
><tr id="gr_svn7768_2481"

><td id="2481"><a href="#2481">2481</a></td></tr
><tr id="gr_svn7768_2482"

><td id="2482"><a href="#2482">2482</a></td></tr
><tr id="gr_svn7768_2483"

><td id="2483"><a href="#2483">2483</a></td></tr
><tr id="gr_svn7768_2484"

><td id="2484"><a href="#2484">2484</a></td></tr
><tr id="gr_svn7768_2485"

><td id="2485"><a href="#2485">2485</a></td></tr
><tr id="gr_svn7768_2486"

><td id="2486"><a href="#2486">2486</a></td></tr
><tr id="gr_svn7768_2487"

><td id="2487"><a href="#2487">2487</a></td></tr
><tr id="gr_svn7768_2488"

><td id="2488"><a href="#2488">2488</a></td></tr
><tr id="gr_svn7768_2489"

><td id="2489"><a href="#2489">2489</a></td></tr
><tr id="gr_svn7768_2490"

><td id="2490"><a href="#2490">2490</a></td></tr
><tr id="gr_svn7768_2491"

><td id="2491"><a href="#2491">2491</a></td></tr
><tr id="gr_svn7768_2492"

><td id="2492"><a href="#2492">2492</a></td></tr
><tr id="gr_svn7768_2493"

><td id="2493"><a href="#2493">2493</a></td></tr
><tr id="gr_svn7768_2494"

><td id="2494"><a href="#2494">2494</a></td></tr
><tr id="gr_svn7768_2495"

><td id="2495"><a href="#2495">2495</a></td></tr
><tr id="gr_svn7768_2496"

><td id="2496"><a href="#2496">2496</a></td></tr
><tr id="gr_svn7768_2497"

><td id="2497"><a href="#2497">2497</a></td></tr
><tr id="gr_svn7768_2498"

><td id="2498"><a href="#2498">2498</a></td></tr
><tr id="gr_svn7768_2499"

><td id="2499"><a href="#2499">2499</a></td></tr
><tr id="gr_svn7768_2500"

><td id="2500"><a href="#2500">2500</a></td></tr
><tr id="gr_svn7768_2501"

><td id="2501"><a href="#2501">2501</a></td></tr
><tr id="gr_svn7768_2502"

><td id="2502"><a href="#2502">2502</a></td></tr
><tr id="gr_svn7768_2503"

><td id="2503"><a href="#2503">2503</a></td></tr
><tr id="gr_svn7768_2504"

><td id="2504"><a href="#2504">2504</a></td></tr
><tr id="gr_svn7768_2505"

><td id="2505"><a href="#2505">2505</a></td></tr
><tr id="gr_svn7768_2506"

><td id="2506"><a href="#2506">2506</a></td></tr
><tr id="gr_svn7768_2507"

><td id="2507"><a href="#2507">2507</a></td></tr
><tr id="gr_svn7768_2508"

><td id="2508"><a href="#2508">2508</a></td></tr
><tr id="gr_svn7768_2509"

><td id="2509"><a href="#2509">2509</a></td></tr
><tr id="gr_svn7768_2510"

><td id="2510"><a href="#2510">2510</a></td></tr
><tr id="gr_svn7768_2511"

><td id="2511"><a href="#2511">2511</a></td></tr
><tr id="gr_svn7768_2512"

><td id="2512"><a href="#2512">2512</a></td></tr
><tr id="gr_svn7768_2513"

><td id="2513"><a href="#2513">2513</a></td></tr
><tr id="gr_svn7768_2514"

><td id="2514"><a href="#2514">2514</a></td></tr
><tr id="gr_svn7768_2515"

><td id="2515"><a href="#2515">2515</a></td></tr
><tr id="gr_svn7768_2516"

><td id="2516"><a href="#2516">2516</a></td></tr
><tr id="gr_svn7768_2517"

><td id="2517"><a href="#2517">2517</a></td></tr
><tr id="gr_svn7768_2518"

><td id="2518"><a href="#2518">2518</a></td></tr
><tr id="gr_svn7768_2519"

><td id="2519"><a href="#2519">2519</a></td></tr
><tr id="gr_svn7768_2520"

><td id="2520"><a href="#2520">2520</a></td></tr
><tr id="gr_svn7768_2521"

><td id="2521"><a href="#2521">2521</a></td></tr
><tr id="gr_svn7768_2522"

><td id="2522"><a href="#2522">2522</a></td></tr
><tr id="gr_svn7768_2523"

><td id="2523"><a href="#2523">2523</a></td></tr
><tr id="gr_svn7768_2524"

><td id="2524"><a href="#2524">2524</a></td></tr
><tr id="gr_svn7768_2525"

><td id="2525"><a href="#2525">2525</a></td></tr
><tr id="gr_svn7768_2526"

><td id="2526"><a href="#2526">2526</a></td></tr
><tr id="gr_svn7768_2527"

><td id="2527"><a href="#2527">2527</a></td></tr
><tr id="gr_svn7768_2528"

><td id="2528"><a href="#2528">2528</a></td></tr
><tr id="gr_svn7768_2529"

><td id="2529"><a href="#2529">2529</a></td></tr
><tr id="gr_svn7768_2530"

><td id="2530"><a href="#2530">2530</a></td></tr
><tr id="gr_svn7768_2531"

><td id="2531"><a href="#2531">2531</a></td></tr
><tr id="gr_svn7768_2532"

><td id="2532"><a href="#2532">2532</a></td></tr
><tr id="gr_svn7768_2533"

><td id="2533"><a href="#2533">2533</a></td></tr
><tr id="gr_svn7768_2534"

><td id="2534"><a href="#2534">2534</a></td></tr
><tr id="gr_svn7768_2535"

><td id="2535"><a href="#2535">2535</a></td></tr
><tr id="gr_svn7768_2536"

><td id="2536"><a href="#2536">2536</a></td></tr
><tr id="gr_svn7768_2537"

><td id="2537"><a href="#2537">2537</a></td></tr
><tr id="gr_svn7768_2538"

><td id="2538"><a href="#2538">2538</a></td></tr
><tr id="gr_svn7768_2539"

><td id="2539"><a href="#2539">2539</a></td></tr
><tr id="gr_svn7768_2540"

><td id="2540"><a href="#2540">2540</a></td></tr
><tr id="gr_svn7768_2541"

><td id="2541"><a href="#2541">2541</a></td></tr
><tr id="gr_svn7768_2542"

><td id="2542"><a href="#2542">2542</a></td></tr
><tr id="gr_svn7768_2543"

><td id="2543"><a href="#2543">2543</a></td></tr
><tr id="gr_svn7768_2544"

><td id="2544"><a href="#2544">2544</a></td></tr
><tr id="gr_svn7768_2545"

><td id="2545"><a href="#2545">2545</a></td></tr
><tr id="gr_svn7768_2546"

><td id="2546"><a href="#2546">2546</a></td></tr
><tr id="gr_svn7768_2547"

><td id="2547"><a href="#2547">2547</a></td></tr
><tr id="gr_svn7768_2548"

><td id="2548"><a href="#2548">2548</a></td></tr
><tr id="gr_svn7768_2549"

><td id="2549"><a href="#2549">2549</a></td></tr
><tr id="gr_svn7768_2550"

><td id="2550"><a href="#2550">2550</a></td></tr
><tr id="gr_svn7768_2551"

><td id="2551"><a href="#2551">2551</a></td></tr
><tr id="gr_svn7768_2552"

><td id="2552"><a href="#2552">2552</a></td></tr
><tr id="gr_svn7768_2553"

><td id="2553"><a href="#2553">2553</a></td></tr
><tr id="gr_svn7768_2554"

><td id="2554"><a href="#2554">2554</a></td></tr
><tr id="gr_svn7768_2555"

><td id="2555"><a href="#2555">2555</a></td></tr
><tr id="gr_svn7768_2556"

><td id="2556"><a href="#2556">2556</a></td></tr
><tr id="gr_svn7768_2557"

><td id="2557"><a href="#2557">2557</a></td></tr
><tr id="gr_svn7768_2558"

><td id="2558"><a href="#2558">2558</a></td></tr
><tr id="gr_svn7768_2559"

><td id="2559"><a href="#2559">2559</a></td></tr
><tr id="gr_svn7768_2560"

><td id="2560"><a href="#2560">2560</a></td></tr
><tr id="gr_svn7768_2561"

><td id="2561"><a href="#2561">2561</a></td></tr
><tr id="gr_svn7768_2562"

><td id="2562"><a href="#2562">2562</a></td></tr
><tr id="gr_svn7768_2563"

><td id="2563"><a href="#2563">2563</a></td></tr
><tr id="gr_svn7768_2564"

><td id="2564"><a href="#2564">2564</a></td></tr
><tr id="gr_svn7768_2565"

><td id="2565"><a href="#2565">2565</a></td></tr
><tr id="gr_svn7768_2566"

><td id="2566"><a href="#2566">2566</a></td></tr
><tr id="gr_svn7768_2567"

><td id="2567"><a href="#2567">2567</a></td></tr
><tr id="gr_svn7768_2568"

><td id="2568"><a href="#2568">2568</a></td></tr
><tr id="gr_svn7768_2569"

><td id="2569"><a href="#2569">2569</a></td></tr
><tr id="gr_svn7768_2570"

><td id="2570"><a href="#2570">2570</a></td></tr
><tr id="gr_svn7768_2571"

><td id="2571"><a href="#2571">2571</a></td></tr
><tr id="gr_svn7768_2572"

><td id="2572"><a href="#2572">2572</a></td></tr
><tr id="gr_svn7768_2573"

><td id="2573"><a href="#2573">2573</a></td></tr
><tr id="gr_svn7768_2574"

><td id="2574"><a href="#2574">2574</a></td></tr
><tr id="gr_svn7768_2575"

><td id="2575"><a href="#2575">2575</a></td></tr
><tr id="gr_svn7768_2576"

><td id="2576"><a href="#2576">2576</a></td></tr
><tr id="gr_svn7768_2577"

><td id="2577"><a href="#2577">2577</a></td></tr
><tr id="gr_svn7768_2578"

><td id="2578"><a href="#2578">2578</a></td></tr
><tr id="gr_svn7768_2579"

><td id="2579"><a href="#2579">2579</a></td></tr
><tr id="gr_svn7768_2580"

><td id="2580"><a href="#2580">2580</a></td></tr
><tr id="gr_svn7768_2581"

><td id="2581"><a href="#2581">2581</a></td></tr
><tr id="gr_svn7768_2582"

><td id="2582"><a href="#2582">2582</a></td></tr
><tr id="gr_svn7768_2583"

><td id="2583"><a href="#2583">2583</a></td></tr
><tr id="gr_svn7768_2584"

><td id="2584"><a href="#2584">2584</a></td></tr
><tr id="gr_svn7768_2585"

><td id="2585"><a href="#2585">2585</a></td></tr
><tr id="gr_svn7768_2586"

><td id="2586"><a href="#2586">2586</a></td></tr
><tr id="gr_svn7768_2587"

><td id="2587"><a href="#2587">2587</a></td></tr
><tr id="gr_svn7768_2588"

><td id="2588"><a href="#2588">2588</a></td></tr
><tr id="gr_svn7768_2589"

><td id="2589"><a href="#2589">2589</a></td></tr
><tr id="gr_svn7768_2590"

><td id="2590"><a href="#2590">2590</a></td></tr
><tr id="gr_svn7768_2591"

><td id="2591"><a href="#2591">2591</a></td></tr
><tr id="gr_svn7768_2592"

><td id="2592"><a href="#2592">2592</a></td></tr
><tr id="gr_svn7768_2593"

><td id="2593"><a href="#2593">2593</a></td></tr
><tr id="gr_svn7768_2594"

><td id="2594"><a href="#2594">2594</a></td></tr
><tr id="gr_svn7768_2595"

><td id="2595"><a href="#2595">2595</a></td></tr
><tr id="gr_svn7768_2596"

><td id="2596"><a href="#2596">2596</a></td></tr
><tr id="gr_svn7768_2597"

><td id="2597"><a href="#2597">2597</a></td></tr
><tr id="gr_svn7768_2598"

><td id="2598"><a href="#2598">2598</a></td></tr
><tr id="gr_svn7768_2599"

><td id="2599"><a href="#2599">2599</a></td></tr
><tr id="gr_svn7768_2600"

><td id="2600"><a href="#2600">2600</a></td></tr
><tr id="gr_svn7768_2601"

><td id="2601"><a href="#2601">2601</a></td></tr
><tr id="gr_svn7768_2602"

><td id="2602"><a href="#2602">2602</a></td></tr
><tr id="gr_svn7768_2603"

><td id="2603"><a href="#2603">2603</a></td></tr
><tr id="gr_svn7768_2604"

><td id="2604"><a href="#2604">2604</a></td></tr
><tr id="gr_svn7768_2605"

><td id="2605"><a href="#2605">2605</a></td></tr
><tr id="gr_svn7768_2606"

><td id="2606"><a href="#2606">2606</a></td></tr
><tr id="gr_svn7768_2607"

><td id="2607"><a href="#2607">2607</a></td></tr
><tr id="gr_svn7768_2608"

><td id="2608"><a href="#2608">2608</a></td></tr
><tr id="gr_svn7768_2609"

><td id="2609"><a href="#2609">2609</a></td></tr
><tr id="gr_svn7768_2610"

><td id="2610"><a href="#2610">2610</a></td></tr
><tr id="gr_svn7768_2611"

><td id="2611"><a href="#2611">2611</a></td></tr
><tr id="gr_svn7768_2612"

><td id="2612"><a href="#2612">2612</a></td></tr
><tr id="gr_svn7768_2613"

><td id="2613"><a href="#2613">2613</a></td></tr
><tr id="gr_svn7768_2614"

><td id="2614"><a href="#2614">2614</a></td></tr
><tr id="gr_svn7768_2615"

><td id="2615"><a href="#2615">2615</a></td></tr
><tr id="gr_svn7768_2616"

><td id="2616"><a href="#2616">2616</a></td></tr
><tr id="gr_svn7768_2617"

><td id="2617"><a href="#2617">2617</a></td></tr
><tr id="gr_svn7768_2618"

><td id="2618"><a href="#2618">2618</a></td></tr
><tr id="gr_svn7768_2619"

><td id="2619"><a href="#2619">2619</a></td></tr
><tr id="gr_svn7768_2620"

><td id="2620"><a href="#2620">2620</a></td></tr
><tr id="gr_svn7768_2621"

><td id="2621"><a href="#2621">2621</a></td></tr
><tr id="gr_svn7768_2622"

><td id="2622"><a href="#2622">2622</a></td></tr
><tr id="gr_svn7768_2623"

><td id="2623"><a href="#2623">2623</a></td></tr
><tr id="gr_svn7768_2624"

><td id="2624"><a href="#2624">2624</a></td></tr
><tr id="gr_svn7768_2625"

><td id="2625"><a href="#2625">2625</a></td></tr
><tr id="gr_svn7768_2626"

><td id="2626"><a href="#2626">2626</a></td></tr
><tr id="gr_svn7768_2627"

><td id="2627"><a href="#2627">2627</a></td></tr
><tr id="gr_svn7768_2628"

><td id="2628"><a href="#2628">2628</a></td></tr
><tr id="gr_svn7768_2629"

><td id="2629"><a href="#2629">2629</a></td></tr
><tr id="gr_svn7768_2630"

><td id="2630"><a href="#2630">2630</a></td></tr
><tr id="gr_svn7768_2631"

><td id="2631"><a href="#2631">2631</a></td></tr
><tr id="gr_svn7768_2632"

><td id="2632"><a href="#2632">2632</a></td></tr
><tr id="gr_svn7768_2633"

><td id="2633"><a href="#2633">2633</a></td></tr
><tr id="gr_svn7768_2634"

><td id="2634"><a href="#2634">2634</a></td></tr
><tr id="gr_svn7768_2635"

><td id="2635"><a href="#2635">2635</a></td></tr
><tr id="gr_svn7768_2636"

><td id="2636"><a href="#2636">2636</a></td></tr
><tr id="gr_svn7768_2637"

><td id="2637"><a href="#2637">2637</a></td></tr
><tr id="gr_svn7768_2638"

><td id="2638"><a href="#2638">2638</a></td></tr
><tr id="gr_svn7768_2639"

><td id="2639"><a href="#2639">2639</a></td></tr
><tr id="gr_svn7768_2640"

><td id="2640"><a href="#2640">2640</a></td></tr
><tr id="gr_svn7768_2641"

><td id="2641"><a href="#2641">2641</a></td></tr
><tr id="gr_svn7768_2642"

><td id="2642"><a href="#2642">2642</a></td></tr
><tr id="gr_svn7768_2643"

><td id="2643"><a href="#2643">2643</a></td></tr
><tr id="gr_svn7768_2644"

><td id="2644"><a href="#2644">2644</a></td></tr
><tr id="gr_svn7768_2645"

><td id="2645"><a href="#2645">2645</a></td></tr
><tr id="gr_svn7768_2646"

><td id="2646"><a href="#2646">2646</a></td></tr
><tr id="gr_svn7768_2647"

><td id="2647"><a href="#2647">2647</a></td></tr
><tr id="gr_svn7768_2648"

><td id="2648"><a href="#2648">2648</a></td></tr
><tr id="gr_svn7768_2649"

><td id="2649"><a href="#2649">2649</a></td></tr
><tr id="gr_svn7768_2650"

><td id="2650"><a href="#2650">2650</a></td></tr
><tr id="gr_svn7768_2651"

><td id="2651"><a href="#2651">2651</a></td></tr
><tr id="gr_svn7768_2652"

><td id="2652"><a href="#2652">2652</a></td></tr
><tr id="gr_svn7768_2653"

><td id="2653"><a href="#2653">2653</a></td></tr
><tr id="gr_svn7768_2654"

><td id="2654"><a href="#2654">2654</a></td></tr
><tr id="gr_svn7768_2655"

><td id="2655"><a href="#2655">2655</a></td></tr
><tr id="gr_svn7768_2656"

><td id="2656"><a href="#2656">2656</a></td></tr
><tr id="gr_svn7768_2657"

><td id="2657"><a href="#2657">2657</a></td></tr
><tr id="gr_svn7768_2658"

><td id="2658"><a href="#2658">2658</a></td></tr
><tr id="gr_svn7768_2659"

><td id="2659"><a href="#2659">2659</a></td></tr
><tr id="gr_svn7768_2660"

><td id="2660"><a href="#2660">2660</a></td></tr
><tr id="gr_svn7768_2661"

><td id="2661"><a href="#2661">2661</a></td></tr
><tr id="gr_svn7768_2662"

><td id="2662"><a href="#2662">2662</a></td></tr
><tr id="gr_svn7768_2663"

><td id="2663"><a href="#2663">2663</a></td></tr
><tr id="gr_svn7768_2664"

><td id="2664"><a href="#2664">2664</a></td></tr
><tr id="gr_svn7768_2665"

><td id="2665"><a href="#2665">2665</a></td></tr
><tr id="gr_svn7768_2666"

><td id="2666"><a href="#2666">2666</a></td></tr
><tr id="gr_svn7768_2667"

><td id="2667"><a href="#2667">2667</a></td></tr
><tr id="gr_svn7768_2668"

><td id="2668"><a href="#2668">2668</a></td></tr
><tr id="gr_svn7768_2669"

><td id="2669"><a href="#2669">2669</a></td></tr
><tr id="gr_svn7768_2670"

><td id="2670"><a href="#2670">2670</a></td></tr
><tr id="gr_svn7768_2671"

><td id="2671"><a href="#2671">2671</a></td></tr
><tr id="gr_svn7768_2672"

><td id="2672"><a href="#2672">2672</a></td></tr
><tr id="gr_svn7768_2673"

><td id="2673"><a href="#2673">2673</a></td></tr
><tr id="gr_svn7768_2674"

><td id="2674"><a href="#2674">2674</a></td></tr
><tr id="gr_svn7768_2675"

><td id="2675"><a href="#2675">2675</a></td></tr
><tr id="gr_svn7768_2676"

><td id="2676"><a href="#2676">2676</a></td></tr
><tr id="gr_svn7768_2677"

><td id="2677"><a href="#2677">2677</a></td></tr
><tr id="gr_svn7768_2678"

><td id="2678"><a href="#2678">2678</a></td></tr
><tr id="gr_svn7768_2679"

><td id="2679"><a href="#2679">2679</a></td></tr
><tr id="gr_svn7768_2680"

><td id="2680"><a href="#2680">2680</a></td></tr
><tr id="gr_svn7768_2681"

><td id="2681"><a href="#2681">2681</a></td></tr
><tr id="gr_svn7768_2682"

><td id="2682"><a href="#2682">2682</a></td></tr
><tr id="gr_svn7768_2683"

><td id="2683"><a href="#2683">2683</a></td></tr
><tr id="gr_svn7768_2684"

><td id="2684"><a href="#2684">2684</a></td></tr
><tr id="gr_svn7768_2685"

><td id="2685"><a href="#2685">2685</a></td></tr
><tr id="gr_svn7768_2686"

><td id="2686"><a href="#2686">2686</a></td></tr
><tr id="gr_svn7768_2687"

><td id="2687"><a href="#2687">2687</a></td></tr
><tr id="gr_svn7768_2688"

><td id="2688"><a href="#2688">2688</a></td></tr
><tr id="gr_svn7768_2689"

><td id="2689"><a href="#2689">2689</a></td></tr
><tr id="gr_svn7768_2690"

><td id="2690"><a href="#2690">2690</a></td></tr
><tr id="gr_svn7768_2691"

><td id="2691"><a href="#2691">2691</a></td></tr
><tr id="gr_svn7768_2692"

><td id="2692"><a href="#2692">2692</a></td></tr
><tr id="gr_svn7768_2693"

><td id="2693"><a href="#2693">2693</a></td></tr
><tr id="gr_svn7768_2694"

><td id="2694"><a href="#2694">2694</a></td></tr
><tr id="gr_svn7768_2695"

><td id="2695"><a href="#2695">2695</a></td></tr
><tr id="gr_svn7768_2696"

><td id="2696"><a href="#2696">2696</a></td></tr
><tr id="gr_svn7768_2697"

><td id="2697"><a href="#2697">2697</a></td></tr
><tr id="gr_svn7768_2698"

><td id="2698"><a href="#2698">2698</a></td></tr
><tr id="gr_svn7768_2699"

><td id="2699"><a href="#2699">2699</a></td></tr
><tr id="gr_svn7768_2700"

><td id="2700"><a href="#2700">2700</a></td></tr
><tr id="gr_svn7768_2701"

><td id="2701"><a href="#2701">2701</a></td></tr
><tr id="gr_svn7768_2702"

><td id="2702"><a href="#2702">2702</a></td></tr
><tr id="gr_svn7768_2703"

><td id="2703"><a href="#2703">2703</a></td></tr
><tr id="gr_svn7768_2704"

><td id="2704"><a href="#2704">2704</a></td></tr
><tr id="gr_svn7768_2705"

><td id="2705"><a href="#2705">2705</a></td></tr
><tr id="gr_svn7768_2706"

><td id="2706"><a href="#2706">2706</a></td></tr
><tr id="gr_svn7768_2707"

><td id="2707"><a href="#2707">2707</a></td></tr
><tr id="gr_svn7768_2708"

><td id="2708"><a href="#2708">2708</a></td></tr
><tr id="gr_svn7768_2709"

><td id="2709"><a href="#2709">2709</a></td></tr
><tr id="gr_svn7768_2710"

><td id="2710"><a href="#2710">2710</a></td></tr
><tr id="gr_svn7768_2711"

><td id="2711"><a href="#2711">2711</a></td></tr
><tr id="gr_svn7768_2712"

><td id="2712"><a href="#2712">2712</a></td></tr
><tr id="gr_svn7768_2713"

><td id="2713"><a href="#2713">2713</a></td></tr
><tr id="gr_svn7768_2714"

><td id="2714"><a href="#2714">2714</a></td></tr
><tr id="gr_svn7768_2715"

><td id="2715"><a href="#2715">2715</a></td></tr
><tr id="gr_svn7768_2716"

><td id="2716"><a href="#2716">2716</a></td></tr
><tr id="gr_svn7768_2717"

><td id="2717"><a href="#2717">2717</a></td></tr
><tr id="gr_svn7768_2718"

><td id="2718"><a href="#2718">2718</a></td></tr
><tr id="gr_svn7768_2719"

><td id="2719"><a href="#2719">2719</a></td></tr
><tr id="gr_svn7768_2720"

><td id="2720"><a href="#2720">2720</a></td></tr
><tr id="gr_svn7768_2721"

><td id="2721"><a href="#2721">2721</a></td></tr
><tr id="gr_svn7768_2722"

><td id="2722"><a href="#2722">2722</a></td></tr
><tr id="gr_svn7768_2723"

><td id="2723"><a href="#2723">2723</a></td></tr
><tr id="gr_svn7768_2724"

><td id="2724"><a href="#2724">2724</a></td></tr
><tr id="gr_svn7768_2725"

><td id="2725"><a href="#2725">2725</a></td></tr
><tr id="gr_svn7768_2726"

><td id="2726"><a href="#2726">2726</a></td></tr
><tr id="gr_svn7768_2727"

><td id="2727"><a href="#2727">2727</a></td></tr
><tr id="gr_svn7768_2728"

><td id="2728"><a href="#2728">2728</a></td></tr
><tr id="gr_svn7768_2729"

><td id="2729"><a href="#2729">2729</a></td></tr
><tr id="gr_svn7768_2730"

><td id="2730"><a href="#2730">2730</a></td></tr
><tr id="gr_svn7768_2731"

><td id="2731"><a href="#2731">2731</a></td></tr
><tr id="gr_svn7768_2732"

><td id="2732"><a href="#2732">2732</a></td></tr
><tr id="gr_svn7768_2733"

><td id="2733"><a href="#2733">2733</a></td></tr
><tr id="gr_svn7768_2734"

><td id="2734"><a href="#2734">2734</a></td></tr
><tr id="gr_svn7768_2735"

><td id="2735"><a href="#2735">2735</a></td></tr
><tr id="gr_svn7768_2736"

><td id="2736"><a href="#2736">2736</a></td></tr
><tr id="gr_svn7768_2737"

><td id="2737"><a href="#2737">2737</a></td></tr
><tr id="gr_svn7768_2738"

><td id="2738"><a href="#2738">2738</a></td></tr
><tr id="gr_svn7768_2739"

><td id="2739"><a href="#2739">2739</a></td></tr
><tr id="gr_svn7768_2740"

><td id="2740"><a href="#2740">2740</a></td></tr
><tr id="gr_svn7768_2741"

><td id="2741"><a href="#2741">2741</a></td></tr
><tr id="gr_svn7768_2742"

><td id="2742"><a href="#2742">2742</a></td></tr
><tr id="gr_svn7768_2743"

><td id="2743"><a href="#2743">2743</a></td></tr
><tr id="gr_svn7768_2744"

><td id="2744"><a href="#2744">2744</a></td></tr
><tr id="gr_svn7768_2745"

><td id="2745"><a href="#2745">2745</a></td></tr
><tr id="gr_svn7768_2746"

><td id="2746"><a href="#2746">2746</a></td></tr
><tr id="gr_svn7768_2747"

><td id="2747"><a href="#2747">2747</a></td></tr
><tr id="gr_svn7768_2748"

><td id="2748"><a href="#2748">2748</a></td></tr
><tr id="gr_svn7768_2749"

><td id="2749"><a href="#2749">2749</a></td></tr
><tr id="gr_svn7768_2750"

><td id="2750"><a href="#2750">2750</a></td></tr
><tr id="gr_svn7768_2751"

><td id="2751"><a href="#2751">2751</a></td></tr
><tr id="gr_svn7768_2752"

><td id="2752"><a href="#2752">2752</a></td></tr
><tr id="gr_svn7768_2753"

><td id="2753"><a href="#2753">2753</a></td></tr
><tr id="gr_svn7768_2754"

><td id="2754"><a href="#2754">2754</a></td></tr
><tr id="gr_svn7768_2755"

><td id="2755"><a href="#2755">2755</a></td></tr
><tr id="gr_svn7768_2756"

><td id="2756"><a href="#2756">2756</a></td></tr
><tr id="gr_svn7768_2757"

><td id="2757"><a href="#2757">2757</a></td></tr
><tr id="gr_svn7768_2758"

><td id="2758"><a href="#2758">2758</a></td></tr
><tr id="gr_svn7768_2759"

><td id="2759"><a href="#2759">2759</a></td></tr
><tr id="gr_svn7768_2760"

><td id="2760"><a href="#2760">2760</a></td></tr
><tr id="gr_svn7768_2761"

><td id="2761"><a href="#2761">2761</a></td></tr
><tr id="gr_svn7768_2762"

><td id="2762"><a href="#2762">2762</a></td></tr
><tr id="gr_svn7768_2763"

><td id="2763"><a href="#2763">2763</a></td></tr
><tr id="gr_svn7768_2764"

><td id="2764"><a href="#2764">2764</a></td></tr
><tr id="gr_svn7768_2765"

><td id="2765"><a href="#2765">2765</a></td></tr
><tr id="gr_svn7768_2766"

><td id="2766"><a href="#2766">2766</a></td></tr
><tr id="gr_svn7768_2767"

><td id="2767"><a href="#2767">2767</a></td></tr
><tr id="gr_svn7768_2768"

><td id="2768"><a href="#2768">2768</a></td></tr
><tr id="gr_svn7768_2769"

><td id="2769"><a href="#2769">2769</a></td></tr
><tr id="gr_svn7768_2770"

><td id="2770"><a href="#2770">2770</a></td></tr
><tr id="gr_svn7768_2771"

><td id="2771"><a href="#2771">2771</a></td></tr
><tr id="gr_svn7768_2772"

><td id="2772"><a href="#2772">2772</a></td></tr
><tr id="gr_svn7768_2773"

><td id="2773"><a href="#2773">2773</a></td></tr
><tr id="gr_svn7768_2774"

><td id="2774"><a href="#2774">2774</a></td></tr
><tr id="gr_svn7768_2775"

><td id="2775"><a href="#2775">2775</a></td></tr
><tr id="gr_svn7768_2776"

><td id="2776"><a href="#2776">2776</a></td></tr
><tr id="gr_svn7768_2777"

><td id="2777"><a href="#2777">2777</a></td></tr
><tr id="gr_svn7768_2778"

><td id="2778"><a href="#2778">2778</a></td></tr
><tr id="gr_svn7768_2779"

><td id="2779"><a href="#2779">2779</a></td></tr
><tr id="gr_svn7768_2780"

><td id="2780"><a href="#2780">2780</a></td></tr
><tr id="gr_svn7768_2781"

><td id="2781"><a href="#2781">2781</a></td></tr
><tr id="gr_svn7768_2782"

><td id="2782"><a href="#2782">2782</a></td></tr
><tr id="gr_svn7768_2783"

><td id="2783"><a href="#2783">2783</a></td></tr
><tr id="gr_svn7768_2784"

><td id="2784"><a href="#2784">2784</a></td></tr
><tr id="gr_svn7768_2785"

><td id="2785"><a href="#2785">2785</a></td></tr
><tr id="gr_svn7768_2786"

><td id="2786"><a href="#2786">2786</a></td></tr
><tr id="gr_svn7768_2787"

><td id="2787"><a href="#2787">2787</a></td></tr
><tr id="gr_svn7768_2788"

><td id="2788"><a href="#2788">2788</a></td></tr
><tr id="gr_svn7768_2789"

><td id="2789"><a href="#2789">2789</a></td></tr
><tr id="gr_svn7768_2790"

><td id="2790"><a href="#2790">2790</a></td></tr
><tr id="gr_svn7768_2791"

><td id="2791"><a href="#2791">2791</a></td></tr
><tr id="gr_svn7768_2792"

><td id="2792"><a href="#2792">2792</a></td></tr
><tr id="gr_svn7768_2793"

><td id="2793"><a href="#2793">2793</a></td></tr
><tr id="gr_svn7768_2794"

><td id="2794"><a href="#2794">2794</a></td></tr
><tr id="gr_svn7768_2795"

><td id="2795"><a href="#2795">2795</a></td></tr
><tr id="gr_svn7768_2796"

><td id="2796"><a href="#2796">2796</a></td></tr
><tr id="gr_svn7768_2797"

><td id="2797"><a href="#2797">2797</a></td></tr
><tr id="gr_svn7768_2798"

><td id="2798"><a href="#2798">2798</a></td></tr
><tr id="gr_svn7768_2799"

><td id="2799"><a href="#2799">2799</a></td></tr
><tr id="gr_svn7768_2800"

><td id="2800"><a href="#2800">2800</a></td></tr
><tr id="gr_svn7768_2801"

><td id="2801"><a href="#2801">2801</a></td></tr
><tr id="gr_svn7768_2802"

><td id="2802"><a href="#2802">2802</a></td></tr
><tr id="gr_svn7768_2803"

><td id="2803"><a href="#2803">2803</a></td></tr
><tr id="gr_svn7768_2804"

><td id="2804"><a href="#2804">2804</a></td></tr
><tr id="gr_svn7768_2805"

><td id="2805"><a href="#2805">2805</a></td></tr
><tr id="gr_svn7768_2806"

><td id="2806"><a href="#2806">2806</a></td></tr
><tr id="gr_svn7768_2807"

><td id="2807"><a href="#2807">2807</a></td></tr
><tr id="gr_svn7768_2808"

><td id="2808"><a href="#2808">2808</a></td></tr
><tr id="gr_svn7768_2809"

><td id="2809"><a href="#2809">2809</a></td></tr
><tr id="gr_svn7768_2810"

><td id="2810"><a href="#2810">2810</a></td></tr
><tr id="gr_svn7768_2811"

><td id="2811"><a href="#2811">2811</a></td></tr
><tr id="gr_svn7768_2812"

><td id="2812"><a href="#2812">2812</a></td></tr
><tr id="gr_svn7768_2813"

><td id="2813"><a href="#2813">2813</a></td></tr
><tr id="gr_svn7768_2814"

><td id="2814"><a href="#2814">2814</a></td></tr
><tr id="gr_svn7768_2815"

><td id="2815"><a href="#2815">2815</a></td></tr
><tr id="gr_svn7768_2816"

><td id="2816"><a href="#2816">2816</a></td></tr
><tr id="gr_svn7768_2817"

><td id="2817"><a href="#2817">2817</a></td></tr
><tr id="gr_svn7768_2818"

><td id="2818"><a href="#2818">2818</a></td></tr
><tr id="gr_svn7768_2819"

><td id="2819"><a href="#2819">2819</a></td></tr
><tr id="gr_svn7768_2820"

><td id="2820"><a href="#2820">2820</a></td></tr
><tr id="gr_svn7768_2821"

><td id="2821"><a href="#2821">2821</a></td></tr
><tr id="gr_svn7768_2822"

><td id="2822"><a href="#2822">2822</a></td></tr
><tr id="gr_svn7768_2823"

><td id="2823"><a href="#2823">2823</a></td></tr
><tr id="gr_svn7768_2824"

><td id="2824"><a href="#2824">2824</a></td></tr
><tr id="gr_svn7768_2825"

><td id="2825"><a href="#2825">2825</a></td></tr
><tr id="gr_svn7768_2826"

><td id="2826"><a href="#2826">2826</a></td></tr
><tr id="gr_svn7768_2827"

><td id="2827"><a href="#2827">2827</a></td></tr
><tr id="gr_svn7768_2828"

><td id="2828"><a href="#2828">2828</a></td></tr
><tr id="gr_svn7768_2829"

><td id="2829"><a href="#2829">2829</a></td></tr
><tr id="gr_svn7768_2830"

><td id="2830"><a href="#2830">2830</a></td></tr
><tr id="gr_svn7768_2831"

><td id="2831"><a href="#2831">2831</a></td></tr
><tr id="gr_svn7768_2832"

><td id="2832"><a href="#2832">2832</a></td></tr
><tr id="gr_svn7768_2833"

><td id="2833"><a href="#2833">2833</a></td></tr
><tr id="gr_svn7768_2834"

><td id="2834"><a href="#2834">2834</a></td></tr
><tr id="gr_svn7768_2835"

><td id="2835"><a href="#2835">2835</a></td></tr
><tr id="gr_svn7768_2836"

><td id="2836"><a href="#2836">2836</a></td></tr
><tr id="gr_svn7768_2837"

><td id="2837"><a href="#2837">2837</a></td></tr
><tr id="gr_svn7768_2838"

><td id="2838"><a href="#2838">2838</a></td></tr
><tr id="gr_svn7768_2839"

><td id="2839"><a href="#2839">2839</a></td></tr
><tr id="gr_svn7768_2840"

><td id="2840"><a href="#2840">2840</a></td></tr
><tr id="gr_svn7768_2841"

><td id="2841"><a href="#2841">2841</a></td></tr
><tr id="gr_svn7768_2842"

><td id="2842"><a href="#2842">2842</a></td></tr
><tr id="gr_svn7768_2843"

><td id="2843"><a href="#2843">2843</a></td></tr
><tr id="gr_svn7768_2844"

><td id="2844"><a href="#2844">2844</a></td></tr
><tr id="gr_svn7768_2845"

><td id="2845"><a href="#2845">2845</a></td></tr
><tr id="gr_svn7768_2846"

><td id="2846"><a href="#2846">2846</a></td></tr
><tr id="gr_svn7768_2847"

><td id="2847"><a href="#2847">2847</a></td></tr
><tr id="gr_svn7768_2848"

><td id="2848"><a href="#2848">2848</a></td></tr
><tr id="gr_svn7768_2849"

><td id="2849"><a href="#2849">2849</a></td></tr
><tr id="gr_svn7768_2850"

><td id="2850"><a href="#2850">2850</a></td></tr
><tr id="gr_svn7768_2851"

><td id="2851"><a href="#2851">2851</a></td></tr
><tr id="gr_svn7768_2852"

><td id="2852"><a href="#2852">2852</a></td></tr
><tr id="gr_svn7768_2853"

><td id="2853"><a href="#2853">2853</a></td></tr
><tr id="gr_svn7768_2854"

><td id="2854"><a href="#2854">2854</a></td></tr
><tr id="gr_svn7768_2855"

><td id="2855"><a href="#2855">2855</a></td></tr
><tr id="gr_svn7768_2856"

><td id="2856"><a href="#2856">2856</a></td></tr
><tr id="gr_svn7768_2857"

><td id="2857"><a href="#2857">2857</a></td></tr
><tr id="gr_svn7768_2858"

><td id="2858"><a href="#2858">2858</a></td></tr
><tr id="gr_svn7768_2859"

><td id="2859"><a href="#2859">2859</a></td></tr
><tr id="gr_svn7768_2860"

><td id="2860"><a href="#2860">2860</a></td></tr
><tr id="gr_svn7768_2861"

><td id="2861"><a href="#2861">2861</a></td></tr
><tr id="gr_svn7768_2862"

><td id="2862"><a href="#2862">2862</a></td></tr
><tr id="gr_svn7768_2863"

><td id="2863"><a href="#2863">2863</a></td></tr
><tr id="gr_svn7768_2864"

><td id="2864"><a href="#2864">2864</a></td></tr
><tr id="gr_svn7768_2865"

><td id="2865"><a href="#2865">2865</a></td></tr
><tr id="gr_svn7768_2866"

><td id="2866"><a href="#2866">2866</a></td></tr
><tr id="gr_svn7768_2867"

><td id="2867"><a href="#2867">2867</a></td></tr
><tr id="gr_svn7768_2868"

><td id="2868"><a href="#2868">2868</a></td></tr
><tr id="gr_svn7768_2869"

><td id="2869"><a href="#2869">2869</a></td></tr
><tr id="gr_svn7768_2870"

><td id="2870"><a href="#2870">2870</a></td></tr
><tr id="gr_svn7768_2871"

><td id="2871"><a href="#2871">2871</a></td></tr
><tr id="gr_svn7768_2872"

><td id="2872"><a href="#2872">2872</a></td></tr
><tr id="gr_svn7768_2873"

><td id="2873"><a href="#2873">2873</a></td></tr
><tr id="gr_svn7768_2874"

><td id="2874"><a href="#2874">2874</a></td></tr
><tr id="gr_svn7768_2875"

><td id="2875"><a href="#2875">2875</a></td></tr
><tr id="gr_svn7768_2876"

><td id="2876"><a href="#2876">2876</a></td></tr
><tr id="gr_svn7768_2877"

><td id="2877"><a href="#2877">2877</a></td></tr
><tr id="gr_svn7768_2878"

><td id="2878"><a href="#2878">2878</a></td></tr
><tr id="gr_svn7768_2879"

><td id="2879"><a href="#2879">2879</a></td></tr
><tr id="gr_svn7768_2880"

><td id="2880"><a href="#2880">2880</a></td></tr
><tr id="gr_svn7768_2881"

><td id="2881"><a href="#2881">2881</a></td></tr
><tr id="gr_svn7768_2882"

><td id="2882"><a href="#2882">2882</a></td></tr
><tr id="gr_svn7768_2883"

><td id="2883"><a href="#2883">2883</a></td></tr
><tr id="gr_svn7768_2884"

><td id="2884"><a href="#2884">2884</a></td></tr
><tr id="gr_svn7768_2885"

><td id="2885"><a href="#2885">2885</a></td></tr
><tr id="gr_svn7768_2886"

><td id="2886"><a href="#2886">2886</a></td></tr
><tr id="gr_svn7768_2887"

><td id="2887"><a href="#2887">2887</a></td></tr
><tr id="gr_svn7768_2888"

><td id="2888"><a href="#2888">2888</a></td></tr
><tr id="gr_svn7768_2889"

><td id="2889"><a href="#2889">2889</a></td></tr
><tr id="gr_svn7768_2890"

><td id="2890"><a href="#2890">2890</a></td></tr
><tr id="gr_svn7768_2891"

><td id="2891"><a href="#2891">2891</a></td></tr
><tr id="gr_svn7768_2892"

><td id="2892"><a href="#2892">2892</a></td></tr
><tr id="gr_svn7768_2893"

><td id="2893"><a href="#2893">2893</a></td></tr
><tr id="gr_svn7768_2894"

><td id="2894"><a href="#2894">2894</a></td></tr
><tr id="gr_svn7768_2895"

><td id="2895"><a href="#2895">2895</a></td></tr
><tr id="gr_svn7768_2896"

><td id="2896"><a href="#2896">2896</a></td></tr
><tr id="gr_svn7768_2897"

><td id="2897"><a href="#2897">2897</a></td></tr
><tr id="gr_svn7768_2898"

><td id="2898"><a href="#2898">2898</a></td></tr
><tr id="gr_svn7768_2899"

><td id="2899"><a href="#2899">2899</a></td></tr
><tr id="gr_svn7768_2900"

><td id="2900"><a href="#2900">2900</a></td></tr
><tr id="gr_svn7768_2901"

><td id="2901"><a href="#2901">2901</a></td></tr
><tr id="gr_svn7768_2902"

><td id="2902"><a href="#2902">2902</a></td></tr
><tr id="gr_svn7768_2903"

><td id="2903"><a href="#2903">2903</a></td></tr
><tr id="gr_svn7768_2904"

><td id="2904"><a href="#2904">2904</a></td></tr
><tr id="gr_svn7768_2905"

><td id="2905"><a href="#2905">2905</a></td></tr
><tr id="gr_svn7768_2906"

><td id="2906"><a href="#2906">2906</a></td></tr
><tr id="gr_svn7768_2907"

><td id="2907"><a href="#2907">2907</a></td></tr
><tr id="gr_svn7768_2908"

><td id="2908"><a href="#2908">2908</a></td></tr
><tr id="gr_svn7768_2909"

><td id="2909"><a href="#2909">2909</a></td></tr
><tr id="gr_svn7768_2910"

><td id="2910"><a href="#2910">2910</a></td></tr
><tr id="gr_svn7768_2911"

><td id="2911"><a href="#2911">2911</a></td></tr
><tr id="gr_svn7768_2912"

><td id="2912"><a href="#2912">2912</a></td></tr
><tr id="gr_svn7768_2913"

><td id="2913"><a href="#2913">2913</a></td></tr
><tr id="gr_svn7768_2914"

><td id="2914"><a href="#2914">2914</a></td></tr
><tr id="gr_svn7768_2915"

><td id="2915"><a href="#2915">2915</a></td></tr
><tr id="gr_svn7768_2916"

><td id="2916"><a href="#2916">2916</a></td></tr
><tr id="gr_svn7768_2917"

><td id="2917"><a href="#2917">2917</a></td></tr
><tr id="gr_svn7768_2918"

><td id="2918"><a href="#2918">2918</a></td></tr
><tr id="gr_svn7768_2919"

><td id="2919"><a href="#2919">2919</a></td></tr
><tr id="gr_svn7768_2920"

><td id="2920"><a href="#2920">2920</a></td></tr
><tr id="gr_svn7768_2921"

><td id="2921"><a href="#2921">2921</a></td></tr
><tr id="gr_svn7768_2922"

><td id="2922"><a href="#2922">2922</a></td></tr
><tr id="gr_svn7768_2923"

><td id="2923"><a href="#2923">2923</a></td></tr
><tr id="gr_svn7768_2924"

><td id="2924"><a href="#2924">2924</a></td></tr
><tr id="gr_svn7768_2925"

><td id="2925"><a href="#2925">2925</a></td></tr
><tr id="gr_svn7768_2926"

><td id="2926"><a href="#2926">2926</a></td></tr
><tr id="gr_svn7768_2927"

><td id="2927"><a href="#2927">2927</a></td></tr
><tr id="gr_svn7768_2928"

><td id="2928"><a href="#2928">2928</a></td></tr
><tr id="gr_svn7768_2929"

><td id="2929"><a href="#2929">2929</a></td></tr
><tr id="gr_svn7768_2930"

><td id="2930"><a href="#2930">2930</a></td></tr
><tr id="gr_svn7768_2931"

><td id="2931"><a href="#2931">2931</a></td></tr
><tr id="gr_svn7768_2932"

><td id="2932"><a href="#2932">2932</a></td></tr
><tr id="gr_svn7768_2933"

><td id="2933"><a href="#2933">2933</a></td></tr
><tr id="gr_svn7768_2934"

><td id="2934"><a href="#2934">2934</a></td></tr
><tr id="gr_svn7768_2935"

><td id="2935"><a href="#2935">2935</a></td></tr
><tr id="gr_svn7768_2936"

><td id="2936"><a href="#2936">2936</a></td></tr
><tr id="gr_svn7768_2937"

><td id="2937"><a href="#2937">2937</a></td></tr
><tr id="gr_svn7768_2938"

><td id="2938"><a href="#2938">2938</a></td></tr
><tr id="gr_svn7768_2939"

><td id="2939"><a href="#2939">2939</a></td></tr
><tr id="gr_svn7768_2940"

><td id="2940"><a href="#2940">2940</a></td></tr
><tr id="gr_svn7768_2941"

><td id="2941"><a href="#2941">2941</a></td></tr
><tr id="gr_svn7768_2942"

><td id="2942"><a href="#2942">2942</a></td></tr
><tr id="gr_svn7768_2943"

><td id="2943"><a href="#2943">2943</a></td></tr
><tr id="gr_svn7768_2944"

><td id="2944"><a href="#2944">2944</a></td></tr
><tr id="gr_svn7768_2945"

><td id="2945"><a href="#2945">2945</a></td></tr
><tr id="gr_svn7768_2946"

><td id="2946"><a href="#2946">2946</a></td></tr
><tr id="gr_svn7768_2947"

><td id="2947"><a href="#2947">2947</a></td></tr
><tr id="gr_svn7768_2948"

><td id="2948"><a href="#2948">2948</a></td></tr
><tr id="gr_svn7768_2949"

><td id="2949"><a href="#2949">2949</a></td></tr
><tr id="gr_svn7768_2950"

><td id="2950"><a href="#2950">2950</a></td></tr
><tr id="gr_svn7768_2951"

><td id="2951"><a href="#2951">2951</a></td></tr
><tr id="gr_svn7768_2952"

><td id="2952"><a href="#2952">2952</a></td></tr
><tr id="gr_svn7768_2953"

><td id="2953"><a href="#2953">2953</a></td></tr
><tr id="gr_svn7768_2954"

><td id="2954"><a href="#2954">2954</a></td></tr
><tr id="gr_svn7768_2955"

><td id="2955"><a href="#2955">2955</a></td></tr
><tr id="gr_svn7768_2956"

><td id="2956"><a href="#2956">2956</a></td></tr
><tr id="gr_svn7768_2957"

><td id="2957"><a href="#2957">2957</a></td></tr
><tr id="gr_svn7768_2958"

><td id="2958"><a href="#2958">2958</a></td></tr
><tr id="gr_svn7768_2959"

><td id="2959"><a href="#2959">2959</a></td></tr
><tr id="gr_svn7768_2960"

><td id="2960"><a href="#2960">2960</a></td></tr
><tr id="gr_svn7768_2961"

><td id="2961"><a href="#2961">2961</a></td></tr
><tr id="gr_svn7768_2962"

><td id="2962"><a href="#2962">2962</a></td></tr
><tr id="gr_svn7768_2963"

><td id="2963"><a href="#2963">2963</a></td></tr
><tr id="gr_svn7768_2964"

><td id="2964"><a href="#2964">2964</a></td></tr
><tr id="gr_svn7768_2965"

><td id="2965"><a href="#2965">2965</a></td></tr
><tr id="gr_svn7768_2966"

><td id="2966"><a href="#2966">2966</a></td></tr
><tr id="gr_svn7768_2967"

><td id="2967"><a href="#2967">2967</a></td></tr
><tr id="gr_svn7768_2968"

><td id="2968"><a href="#2968">2968</a></td></tr
><tr id="gr_svn7768_2969"

><td id="2969"><a href="#2969">2969</a></td></tr
><tr id="gr_svn7768_2970"

><td id="2970"><a href="#2970">2970</a></td></tr
><tr id="gr_svn7768_2971"

><td id="2971"><a href="#2971">2971</a></td></tr
><tr id="gr_svn7768_2972"

><td id="2972"><a href="#2972">2972</a></td></tr
><tr id="gr_svn7768_2973"

><td id="2973"><a href="#2973">2973</a></td></tr
><tr id="gr_svn7768_2974"

><td id="2974"><a href="#2974">2974</a></td></tr
><tr id="gr_svn7768_2975"

><td id="2975"><a href="#2975">2975</a></td></tr
><tr id="gr_svn7768_2976"

><td id="2976"><a href="#2976">2976</a></td></tr
><tr id="gr_svn7768_2977"

><td id="2977"><a href="#2977">2977</a></td></tr
><tr id="gr_svn7768_2978"

><td id="2978"><a href="#2978">2978</a></td></tr
><tr id="gr_svn7768_2979"

><td id="2979"><a href="#2979">2979</a></td></tr
><tr id="gr_svn7768_2980"

><td id="2980"><a href="#2980">2980</a></td></tr
><tr id="gr_svn7768_2981"

><td id="2981"><a href="#2981">2981</a></td></tr
><tr id="gr_svn7768_2982"

><td id="2982"><a href="#2982">2982</a></td></tr
><tr id="gr_svn7768_2983"

><td id="2983"><a href="#2983">2983</a></td></tr
><tr id="gr_svn7768_2984"

><td id="2984"><a href="#2984">2984</a></td></tr
><tr id="gr_svn7768_2985"

><td id="2985"><a href="#2985">2985</a></td></tr
><tr id="gr_svn7768_2986"

><td id="2986"><a href="#2986">2986</a></td></tr
><tr id="gr_svn7768_2987"

><td id="2987"><a href="#2987">2987</a></td></tr
><tr id="gr_svn7768_2988"

><td id="2988"><a href="#2988">2988</a></td></tr
><tr id="gr_svn7768_2989"

><td id="2989"><a href="#2989">2989</a></td></tr
><tr id="gr_svn7768_2990"

><td id="2990"><a href="#2990">2990</a></td></tr
><tr id="gr_svn7768_2991"

><td id="2991"><a href="#2991">2991</a></td></tr
><tr id="gr_svn7768_2992"

><td id="2992"><a href="#2992">2992</a></td></tr
><tr id="gr_svn7768_2993"

><td id="2993"><a href="#2993">2993</a></td></tr
><tr id="gr_svn7768_2994"

><td id="2994"><a href="#2994">2994</a></td></tr
><tr id="gr_svn7768_2995"

><td id="2995"><a href="#2995">2995</a></td></tr
><tr id="gr_svn7768_2996"

><td id="2996"><a href="#2996">2996</a></td></tr
><tr id="gr_svn7768_2997"

><td id="2997"><a href="#2997">2997</a></td></tr
><tr id="gr_svn7768_2998"

><td id="2998"><a href="#2998">2998</a></td></tr
><tr id="gr_svn7768_2999"

><td id="2999"><a href="#2999">2999</a></td></tr
><tr id="gr_svn7768_3000"

><td id="3000"><a href="#3000">3000</a></td></tr
><tr id="gr_svn7768_3001"

><td id="3001"><a href="#3001">3001</a></td></tr
><tr id="gr_svn7768_3002"

><td id="3002"><a href="#3002">3002</a></td></tr
><tr id="gr_svn7768_3003"

><td id="3003"><a href="#3003">3003</a></td></tr
><tr id="gr_svn7768_3004"

><td id="3004"><a href="#3004">3004</a></td></tr
><tr id="gr_svn7768_3005"

><td id="3005"><a href="#3005">3005</a></td></tr
><tr id="gr_svn7768_3006"

><td id="3006"><a href="#3006">3006</a></td></tr
><tr id="gr_svn7768_3007"

><td id="3007"><a href="#3007">3007</a></td></tr
><tr id="gr_svn7768_3008"

><td id="3008"><a href="#3008">3008</a></td></tr
><tr id="gr_svn7768_3009"

><td id="3009"><a href="#3009">3009</a></td></tr
><tr id="gr_svn7768_3010"

><td id="3010"><a href="#3010">3010</a></td></tr
><tr id="gr_svn7768_3011"

><td id="3011"><a href="#3011">3011</a></td></tr
><tr id="gr_svn7768_3012"

><td id="3012"><a href="#3012">3012</a></td></tr
><tr id="gr_svn7768_3013"

><td id="3013"><a href="#3013">3013</a></td></tr
><tr id="gr_svn7768_3014"

><td id="3014"><a href="#3014">3014</a></td></tr
><tr id="gr_svn7768_3015"

><td id="3015"><a href="#3015">3015</a></td></tr
><tr id="gr_svn7768_3016"

><td id="3016"><a href="#3016">3016</a></td></tr
><tr id="gr_svn7768_3017"

><td id="3017"><a href="#3017">3017</a></td></tr
><tr id="gr_svn7768_3018"

><td id="3018"><a href="#3018">3018</a></td></tr
><tr id="gr_svn7768_3019"

><td id="3019"><a href="#3019">3019</a></td></tr
><tr id="gr_svn7768_3020"

><td id="3020"><a href="#3020">3020</a></td></tr
><tr id="gr_svn7768_3021"

><td id="3021"><a href="#3021">3021</a></td></tr
><tr id="gr_svn7768_3022"

><td id="3022"><a href="#3022">3022</a></td></tr
><tr id="gr_svn7768_3023"

><td id="3023"><a href="#3023">3023</a></td></tr
><tr id="gr_svn7768_3024"

><td id="3024"><a href="#3024">3024</a></td></tr
><tr id="gr_svn7768_3025"

><td id="3025"><a href="#3025">3025</a></td></tr
><tr id="gr_svn7768_3026"

><td id="3026"><a href="#3026">3026</a></td></tr
><tr id="gr_svn7768_3027"

><td id="3027"><a href="#3027">3027</a></td></tr
><tr id="gr_svn7768_3028"

><td id="3028"><a href="#3028">3028</a></td></tr
><tr id="gr_svn7768_3029"

><td id="3029"><a href="#3029">3029</a></td></tr
><tr id="gr_svn7768_3030"

><td id="3030"><a href="#3030">3030</a></td></tr
><tr id="gr_svn7768_3031"

><td id="3031"><a href="#3031">3031</a></td></tr
><tr id="gr_svn7768_3032"

><td id="3032"><a href="#3032">3032</a></td></tr
><tr id="gr_svn7768_3033"

><td id="3033"><a href="#3033">3033</a></td></tr
><tr id="gr_svn7768_3034"

><td id="3034"><a href="#3034">3034</a></td></tr
><tr id="gr_svn7768_3035"

><td id="3035"><a href="#3035">3035</a></td></tr
><tr id="gr_svn7768_3036"

><td id="3036"><a href="#3036">3036</a></td></tr
><tr id="gr_svn7768_3037"

><td id="3037"><a href="#3037">3037</a></td></tr
><tr id="gr_svn7768_3038"

><td id="3038"><a href="#3038">3038</a></td></tr
><tr id="gr_svn7768_3039"

><td id="3039"><a href="#3039">3039</a></td></tr
><tr id="gr_svn7768_3040"

><td id="3040"><a href="#3040">3040</a></td></tr
><tr id="gr_svn7768_3041"

><td id="3041"><a href="#3041">3041</a></td></tr
><tr id="gr_svn7768_3042"

><td id="3042"><a href="#3042">3042</a></td></tr
><tr id="gr_svn7768_3043"

><td id="3043"><a href="#3043">3043</a></td></tr
><tr id="gr_svn7768_3044"

><td id="3044"><a href="#3044">3044</a></td></tr
><tr id="gr_svn7768_3045"

><td id="3045"><a href="#3045">3045</a></td></tr
><tr id="gr_svn7768_3046"

><td id="3046"><a href="#3046">3046</a></td></tr
><tr id="gr_svn7768_3047"

><td id="3047"><a href="#3047">3047</a></td></tr
><tr id="gr_svn7768_3048"

><td id="3048"><a href="#3048">3048</a></td></tr
><tr id="gr_svn7768_3049"

><td id="3049"><a href="#3049">3049</a></td></tr
><tr id="gr_svn7768_3050"

><td id="3050"><a href="#3050">3050</a></td></tr
><tr id="gr_svn7768_3051"

><td id="3051"><a href="#3051">3051</a></td></tr
><tr id="gr_svn7768_3052"

><td id="3052"><a href="#3052">3052</a></td></tr
><tr id="gr_svn7768_3053"

><td id="3053"><a href="#3053">3053</a></td></tr
><tr id="gr_svn7768_3054"

><td id="3054"><a href="#3054">3054</a></td></tr
><tr id="gr_svn7768_3055"

><td id="3055"><a href="#3055">3055</a></td></tr
><tr id="gr_svn7768_3056"

><td id="3056"><a href="#3056">3056</a></td></tr
><tr id="gr_svn7768_3057"

><td id="3057"><a href="#3057">3057</a></td></tr
><tr id="gr_svn7768_3058"

><td id="3058"><a href="#3058">3058</a></td></tr
><tr id="gr_svn7768_3059"

><td id="3059"><a href="#3059">3059</a></td></tr
><tr id="gr_svn7768_3060"

><td id="3060"><a href="#3060">3060</a></td></tr
><tr id="gr_svn7768_3061"

><td id="3061"><a href="#3061">3061</a></td></tr
><tr id="gr_svn7768_3062"

><td id="3062"><a href="#3062">3062</a></td></tr
><tr id="gr_svn7768_3063"

><td id="3063"><a href="#3063">3063</a></td></tr
><tr id="gr_svn7768_3064"

><td id="3064"><a href="#3064">3064</a></td></tr
><tr id="gr_svn7768_3065"

><td id="3065"><a href="#3065">3065</a></td></tr
><tr id="gr_svn7768_3066"

><td id="3066"><a href="#3066">3066</a></td></tr
><tr id="gr_svn7768_3067"

><td id="3067"><a href="#3067">3067</a></td></tr
><tr id="gr_svn7768_3068"

><td id="3068"><a href="#3068">3068</a></td></tr
><tr id="gr_svn7768_3069"

><td id="3069"><a href="#3069">3069</a></td></tr
><tr id="gr_svn7768_3070"

><td id="3070"><a href="#3070">3070</a></td></tr
><tr id="gr_svn7768_3071"

><td id="3071"><a href="#3071">3071</a></td></tr
><tr id="gr_svn7768_3072"

><td id="3072"><a href="#3072">3072</a></td></tr
><tr id="gr_svn7768_3073"

><td id="3073"><a href="#3073">3073</a></td></tr
><tr id="gr_svn7768_3074"

><td id="3074"><a href="#3074">3074</a></td></tr
><tr id="gr_svn7768_3075"

><td id="3075"><a href="#3075">3075</a></td></tr
><tr id="gr_svn7768_3076"

><td id="3076"><a href="#3076">3076</a></td></tr
><tr id="gr_svn7768_3077"

><td id="3077"><a href="#3077">3077</a></td></tr
><tr id="gr_svn7768_3078"

><td id="3078"><a href="#3078">3078</a></td></tr
><tr id="gr_svn7768_3079"

><td id="3079"><a href="#3079">3079</a></td></tr
><tr id="gr_svn7768_3080"

><td id="3080"><a href="#3080">3080</a></td></tr
><tr id="gr_svn7768_3081"

><td id="3081"><a href="#3081">3081</a></td></tr
><tr id="gr_svn7768_3082"

><td id="3082"><a href="#3082">3082</a></td></tr
><tr id="gr_svn7768_3083"

><td id="3083"><a href="#3083">3083</a></td></tr
><tr id="gr_svn7768_3084"

><td id="3084"><a href="#3084">3084</a></td></tr
><tr id="gr_svn7768_3085"

><td id="3085"><a href="#3085">3085</a></td></tr
><tr id="gr_svn7768_3086"

><td id="3086"><a href="#3086">3086</a></td></tr
><tr id="gr_svn7768_3087"

><td id="3087"><a href="#3087">3087</a></td></tr
><tr id="gr_svn7768_3088"

><td id="3088"><a href="#3088">3088</a></td></tr
><tr id="gr_svn7768_3089"

><td id="3089"><a href="#3089">3089</a></td></tr
><tr id="gr_svn7768_3090"

><td id="3090"><a href="#3090">3090</a></td></tr
><tr id="gr_svn7768_3091"

><td id="3091"><a href="#3091">3091</a></td></tr
><tr id="gr_svn7768_3092"

><td id="3092"><a href="#3092">3092</a></td></tr
><tr id="gr_svn7768_3093"

><td id="3093"><a href="#3093">3093</a></td></tr
><tr id="gr_svn7768_3094"

><td id="3094"><a href="#3094">3094</a></td></tr
><tr id="gr_svn7768_3095"

><td id="3095"><a href="#3095">3095</a></td></tr
><tr id="gr_svn7768_3096"

><td id="3096"><a href="#3096">3096</a></td></tr
><tr id="gr_svn7768_3097"

><td id="3097"><a href="#3097">3097</a></td></tr
><tr id="gr_svn7768_3098"

><td id="3098"><a href="#3098">3098</a></td></tr
><tr id="gr_svn7768_3099"

><td id="3099"><a href="#3099">3099</a></td></tr
><tr id="gr_svn7768_3100"

><td id="3100"><a href="#3100">3100</a></td></tr
><tr id="gr_svn7768_3101"

><td id="3101"><a href="#3101">3101</a></td></tr
><tr id="gr_svn7768_3102"

><td id="3102"><a href="#3102">3102</a></td></tr
><tr id="gr_svn7768_3103"

><td id="3103"><a href="#3103">3103</a></td></tr
><tr id="gr_svn7768_3104"

><td id="3104"><a href="#3104">3104</a></td></tr
><tr id="gr_svn7768_3105"

><td id="3105"><a href="#3105">3105</a></td></tr
><tr id="gr_svn7768_3106"

><td id="3106"><a href="#3106">3106</a></td></tr
><tr id="gr_svn7768_3107"

><td id="3107"><a href="#3107">3107</a></td></tr
><tr id="gr_svn7768_3108"

><td id="3108"><a href="#3108">3108</a></td></tr
><tr id="gr_svn7768_3109"

><td id="3109"><a href="#3109">3109</a></td></tr
><tr id="gr_svn7768_3110"

><td id="3110"><a href="#3110">3110</a></td></tr
><tr id="gr_svn7768_3111"

><td id="3111"><a href="#3111">3111</a></td></tr
><tr id="gr_svn7768_3112"

><td id="3112"><a href="#3112">3112</a></td></tr
><tr id="gr_svn7768_3113"

><td id="3113"><a href="#3113">3113</a></td></tr
><tr id="gr_svn7768_3114"

><td id="3114"><a href="#3114">3114</a></td></tr
><tr id="gr_svn7768_3115"

><td id="3115"><a href="#3115">3115</a></td></tr
><tr id="gr_svn7768_3116"

><td id="3116"><a href="#3116">3116</a></td></tr
><tr id="gr_svn7768_3117"

><td id="3117"><a href="#3117">3117</a></td></tr
><tr id="gr_svn7768_3118"

><td id="3118"><a href="#3118">3118</a></td></tr
><tr id="gr_svn7768_3119"

><td id="3119"><a href="#3119">3119</a></td></tr
><tr id="gr_svn7768_3120"

><td id="3120"><a href="#3120">3120</a></td></tr
><tr id="gr_svn7768_3121"

><td id="3121"><a href="#3121">3121</a></td></tr
><tr id="gr_svn7768_3122"

><td id="3122"><a href="#3122">3122</a></td></tr
><tr id="gr_svn7768_3123"

><td id="3123"><a href="#3123">3123</a></td></tr
><tr id="gr_svn7768_3124"

><td id="3124"><a href="#3124">3124</a></td></tr
><tr id="gr_svn7768_3125"

><td id="3125"><a href="#3125">3125</a></td></tr
><tr id="gr_svn7768_3126"

><td id="3126"><a href="#3126">3126</a></td></tr
><tr id="gr_svn7768_3127"

><td id="3127"><a href="#3127">3127</a></td></tr
><tr id="gr_svn7768_3128"

><td id="3128"><a href="#3128">3128</a></td></tr
><tr id="gr_svn7768_3129"

><td id="3129"><a href="#3129">3129</a></td></tr
><tr id="gr_svn7768_3130"

><td id="3130"><a href="#3130">3130</a></td></tr
><tr id="gr_svn7768_3131"

><td id="3131"><a href="#3131">3131</a></td></tr
><tr id="gr_svn7768_3132"

><td id="3132"><a href="#3132">3132</a></td></tr
><tr id="gr_svn7768_3133"

><td id="3133"><a href="#3133">3133</a></td></tr
><tr id="gr_svn7768_3134"

><td id="3134"><a href="#3134">3134</a></td></tr
><tr id="gr_svn7768_3135"

><td id="3135"><a href="#3135">3135</a></td></tr
><tr id="gr_svn7768_3136"

><td id="3136"><a href="#3136">3136</a></td></tr
><tr id="gr_svn7768_3137"

><td id="3137"><a href="#3137">3137</a></td></tr
><tr id="gr_svn7768_3138"

><td id="3138"><a href="#3138">3138</a></td></tr
><tr id="gr_svn7768_3139"

><td id="3139"><a href="#3139">3139</a></td></tr
><tr id="gr_svn7768_3140"

><td id="3140"><a href="#3140">3140</a></td></tr
><tr id="gr_svn7768_3141"

><td id="3141"><a href="#3141">3141</a></td></tr
><tr id="gr_svn7768_3142"

><td id="3142"><a href="#3142">3142</a></td></tr
><tr id="gr_svn7768_3143"

><td id="3143"><a href="#3143">3143</a></td></tr
><tr id="gr_svn7768_3144"

><td id="3144"><a href="#3144">3144</a></td></tr
><tr id="gr_svn7768_3145"

><td id="3145"><a href="#3145">3145</a></td></tr
><tr id="gr_svn7768_3146"

><td id="3146"><a href="#3146">3146</a></td></tr
><tr id="gr_svn7768_3147"

><td id="3147"><a href="#3147">3147</a></td></tr
><tr id="gr_svn7768_3148"

><td id="3148"><a href="#3148">3148</a></td></tr
><tr id="gr_svn7768_3149"

><td id="3149"><a href="#3149">3149</a></td></tr
><tr id="gr_svn7768_3150"

><td id="3150"><a href="#3150">3150</a></td></tr
><tr id="gr_svn7768_3151"

><td id="3151"><a href="#3151">3151</a></td></tr
><tr id="gr_svn7768_3152"

><td id="3152"><a href="#3152">3152</a></td></tr
><tr id="gr_svn7768_3153"

><td id="3153"><a href="#3153">3153</a></td></tr
><tr id="gr_svn7768_3154"

><td id="3154"><a href="#3154">3154</a></td></tr
><tr id="gr_svn7768_3155"

><td id="3155"><a href="#3155">3155</a></td></tr
><tr id="gr_svn7768_3156"

><td id="3156"><a href="#3156">3156</a></td></tr
><tr id="gr_svn7768_3157"

><td id="3157"><a href="#3157">3157</a></td></tr
><tr id="gr_svn7768_3158"

><td id="3158"><a href="#3158">3158</a></td></tr
><tr id="gr_svn7768_3159"

><td id="3159"><a href="#3159">3159</a></td></tr
><tr id="gr_svn7768_3160"

><td id="3160"><a href="#3160">3160</a></td></tr
><tr id="gr_svn7768_3161"

><td id="3161"><a href="#3161">3161</a></td></tr
><tr id="gr_svn7768_3162"

><td id="3162"><a href="#3162">3162</a></td></tr
><tr id="gr_svn7768_3163"

><td id="3163"><a href="#3163">3163</a></td></tr
><tr id="gr_svn7768_3164"

><td id="3164"><a href="#3164">3164</a></td></tr
><tr id="gr_svn7768_3165"

><td id="3165"><a href="#3165">3165</a></td></tr
><tr id="gr_svn7768_3166"

><td id="3166"><a href="#3166">3166</a></td></tr
><tr id="gr_svn7768_3167"

><td id="3167"><a href="#3167">3167</a></td></tr
><tr id="gr_svn7768_3168"

><td id="3168"><a href="#3168">3168</a></td></tr
><tr id="gr_svn7768_3169"

><td id="3169"><a href="#3169">3169</a></td></tr
><tr id="gr_svn7768_3170"

><td id="3170"><a href="#3170">3170</a></td></tr
><tr id="gr_svn7768_3171"

><td id="3171"><a href="#3171">3171</a></td></tr
><tr id="gr_svn7768_3172"

><td id="3172"><a href="#3172">3172</a></td></tr
><tr id="gr_svn7768_3173"

><td id="3173"><a href="#3173">3173</a></td></tr
><tr id="gr_svn7768_3174"

><td id="3174"><a href="#3174">3174</a></td></tr
><tr id="gr_svn7768_3175"

><td id="3175"><a href="#3175">3175</a></td></tr
><tr id="gr_svn7768_3176"

><td id="3176"><a href="#3176">3176</a></td></tr
><tr id="gr_svn7768_3177"

><td id="3177"><a href="#3177">3177</a></td></tr
><tr id="gr_svn7768_3178"

><td id="3178"><a href="#3178">3178</a></td></tr
><tr id="gr_svn7768_3179"

><td id="3179"><a href="#3179">3179</a></td></tr
><tr id="gr_svn7768_3180"

><td id="3180"><a href="#3180">3180</a></td></tr
><tr id="gr_svn7768_3181"

><td id="3181"><a href="#3181">3181</a></td></tr
><tr id="gr_svn7768_3182"

><td id="3182"><a href="#3182">3182</a></td></tr
><tr id="gr_svn7768_3183"

><td id="3183"><a href="#3183">3183</a></td></tr
><tr id="gr_svn7768_3184"

><td id="3184"><a href="#3184">3184</a></td></tr
><tr id="gr_svn7768_3185"

><td id="3185"><a href="#3185">3185</a></td></tr
><tr id="gr_svn7768_3186"

><td id="3186"><a href="#3186">3186</a></td></tr
><tr id="gr_svn7768_3187"

><td id="3187"><a href="#3187">3187</a></td></tr
><tr id="gr_svn7768_3188"

><td id="3188"><a href="#3188">3188</a></td></tr
><tr id="gr_svn7768_3189"

><td id="3189"><a href="#3189">3189</a></td></tr
><tr id="gr_svn7768_3190"

><td id="3190"><a href="#3190">3190</a></td></tr
><tr id="gr_svn7768_3191"

><td id="3191"><a href="#3191">3191</a></td></tr
><tr id="gr_svn7768_3192"

><td id="3192"><a href="#3192">3192</a></td></tr
><tr id="gr_svn7768_3193"

><td id="3193"><a href="#3193">3193</a></td></tr
><tr id="gr_svn7768_3194"

><td id="3194"><a href="#3194">3194</a></td></tr
><tr id="gr_svn7768_3195"

><td id="3195"><a href="#3195">3195</a></td></tr
><tr id="gr_svn7768_3196"

><td id="3196"><a href="#3196">3196</a></td></tr
><tr id="gr_svn7768_3197"

><td id="3197"><a href="#3197">3197</a></td></tr
><tr id="gr_svn7768_3198"

><td id="3198"><a href="#3198">3198</a></td></tr
><tr id="gr_svn7768_3199"

><td id="3199"><a href="#3199">3199</a></td></tr
><tr id="gr_svn7768_3200"

><td id="3200"><a href="#3200">3200</a></td></tr
><tr id="gr_svn7768_3201"

><td id="3201"><a href="#3201">3201</a></td></tr
><tr id="gr_svn7768_3202"

><td id="3202"><a href="#3202">3202</a></td></tr
><tr id="gr_svn7768_3203"

><td id="3203"><a href="#3203">3203</a></td></tr
><tr id="gr_svn7768_3204"

><td id="3204"><a href="#3204">3204</a></td></tr
><tr id="gr_svn7768_3205"

><td id="3205"><a href="#3205">3205</a></td></tr
><tr id="gr_svn7768_3206"

><td id="3206"><a href="#3206">3206</a></td></tr
><tr id="gr_svn7768_3207"

><td id="3207"><a href="#3207">3207</a></td></tr
><tr id="gr_svn7768_3208"

><td id="3208"><a href="#3208">3208</a></td></tr
><tr id="gr_svn7768_3209"

><td id="3209"><a href="#3209">3209</a></td></tr
><tr id="gr_svn7768_3210"

><td id="3210"><a href="#3210">3210</a></td></tr
><tr id="gr_svn7768_3211"

><td id="3211"><a href="#3211">3211</a></td></tr
><tr id="gr_svn7768_3212"

><td id="3212"><a href="#3212">3212</a></td></tr
><tr id="gr_svn7768_3213"

><td id="3213"><a href="#3213">3213</a></td></tr
><tr id="gr_svn7768_3214"

><td id="3214"><a href="#3214">3214</a></td></tr
><tr id="gr_svn7768_3215"

><td id="3215"><a href="#3215">3215</a></td></tr
><tr id="gr_svn7768_3216"

><td id="3216"><a href="#3216">3216</a></td></tr
><tr id="gr_svn7768_3217"

><td id="3217"><a href="#3217">3217</a></td></tr
><tr id="gr_svn7768_3218"

><td id="3218"><a href="#3218">3218</a></td></tr
><tr id="gr_svn7768_3219"

><td id="3219"><a href="#3219">3219</a></td></tr
><tr id="gr_svn7768_3220"

><td id="3220"><a href="#3220">3220</a></td></tr
><tr id="gr_svn7768_3221"

><td id="3221"><a href="#3221">3221</a></td></tr
><tr id="gr_svn7768_3222"

><td id="3222"><a href="#3222">3222</a></td></tr
><tr id="gr_svn7768_3223"

><td id="3223"><a href="#3223">3223</a></td></tr
><tr id="gr_svn7768_3224"

><td id="3224"><a href="#3224">3224</a></td></tr
><tr id="gr_svn7768_3225"

><td id="3225"><a href="#3225">3225</a></td></tr
><tr id="gr_svn7768_3226"

><td id="3226"><a href="#3226">3226</a></td></tr
><tr id="gr_svn7768_3227"

><td id="3227"><a href="#3227">3227</a></td></tr
><tr id="gr_svn7768_3228"

><td id="3228"><a href="#3228">3228</a></td></tr
><tr id="gr_svn7768_3229"

><td id="3229"><a href="#3229">3229</a></td></tr
><tr id="gr_svn7768_3230"

><td id="3230"><a href="#3230">3230</a></td></tr
><tr id="gr_svn7768_3231"

><td id="3231"><a href="#3231">3231</a></td></tr
><tr id="gr_svn7768_3232"

><td id="3232"><a href="#3232">3232</a></td></tr
><tr id="gr_svn7768_3233"

><td id="3233"><a href="#3233">3233</a></td></tr
><tr id="gr_svn7768_3234"

><td id="3234"><a href="#3234">3234</a></td></tr
><tr id="gr_svn7768_3235"

><td id="3235"><a href="#3235">3235</a></td></tr
><tr id="gr_svn7768_3236"

><td id="3236"><a href="#3236">3236</a></td></tr
><tr id="gr_svn7768_3237"

><td id="3237"><a href="#3237">3237</a></td></tr
><tr id="gr_svn7768_3238"

><td id="3238"><a href="#3238">3238</a></td></tr
><tr id="gr_svn7768_3239"

><td id="3239"><a href="#3239">3239</a></td></tr
><tr id="gr_svn7768_3240"

><td id="3240"><a href="#3240">3240</a></td></tr
><tr id="gr_svn7768_3241"

><td id="3241"><a href="#3241">3241</a></td></tr
><tr id="gr_svn7768_3242"

><td id="3242"><a href="#3242">3242</a></td></tr
><tr id="gr_svn7768_3243"

><td id="3243"><a href="#3243">3243</a></td></tr
><tr id="gr_svn7768_3244"

><td id="3244"><a href="#3244">3244</a></td></tr
><tr id="gr_svn7768_3245"

><td id="3245"><a href="#3245">3245</a></td></tr
><tr id="gr_svn7768_3246"

><td id="3246"><a href="#3246">3246</a></td></tr
><tr id="gr_svn7768_3247"

><td id="3247"><a href="#3247">3247</a></td></tr
><tr id="gr_svn7768_3248"

><td id="3248"><a href="#3248">3248</a></td></tr
><tr id="gr_svn7768_3249"

><td id="3249"><a href="#3249">3249</a></td></tr
><tr id="gr_svn7768_3250"

><td id="3250"><a href="#3250">3250</a></td></tr
><tr id="gr_svn7768_3251"

><td id="3251"><a href="#3251">3251</a></td></tr
><tr id="gr_svn7768_3252"

><td id="3252"><a href="#3252">3252</a></td></tr
><tr id="gr_svn7768_3253"

><td id="3253"><a href="#3253">3253</a></td></tr
><tr id="gr_svn7768_3254"

><td id="3254"><a href="#3254">3254</a></td></tr
><tr id="gr_svn7768_3255"

><td id="3255"><a href="#3255">3255</a></td></tr
><tr id="gr_svn7768_3256"

><td id="3256"><a href="#3256">3256</a></td></tr
><tr id="gr_svn7768_3257"

><td id="3257"><a href="#3257">3257</a></td></tr
><tr id="gr_svn7768_3258"

><td id="3258"><a href="#3258">3258</a></td></tr
><tr id="gr_svn7768_3259"

><td id="3259"><a href="#3259">3259</a></td></tr
><tr id="gr_svn7768_3260"

><td id="3260"><a href="#3260">3260</a></td></tr
><tr id="gr_svn7768_3261"

><td id="3261"><a href="#3261">3261</a></td></tr
><tr id="gr_svn7768_3262"

><td id="3262"><a href="#3262">3262</a></td></tr
><tr id="gr_svn7768_3263"

><td id="3263"><a href="#3263">3263</a></td></tr
><tr id="gr_svn7768_3264"

><td id="3264"><a href="#3264">3264</a></td></tr
><tr id="gr_svn7768_3265"

><td id="3265"><a href="#3265">3265</a></td></tr
><tr id="gr_svn7768_3266"

><td id="3266"><a href="#3266">3266</a></td></tr
><tr id="gr_svn7768_3267"

><td id="3267"><a href="#3267">3267</a></td></tr
><tr id="gr_svn7768_3268"

><td id="3268"><a href="#3268">3268</a></td></tr
><tr id="gr_svn7768_3269"

><td id="3269"><a href="#3269">3269</a></td></tr
><tr id="gr_svn7768_3270"

><td id="3270"><a href="#3270">3270</a></td></tr
><tr id="gr_svn7768_3271"

><td id="3271"><a href="#3271">3271</a></td></tr
><tr id="gr_svn7768_3272"

><td id="3272"><a href="#3272">3272</a></td></tr
><tr id="gr_svn7768_3273"

><td id="3273"><a href="#3273">3273</a></td></tr
><tr id="gr_svn7768_3274"

><td id="3274"><a href="#3274">3274</a></td></tr
><tr id="gr_svn7768_3275"

><td id="3275"><a href="#3275">3275</a></td></tr
><tr id="gr_svn7768_3276"

><td id="3276"><a href="#3276">3276</a></td></tr
><tr id="gr_svn7768_3277"

><td id="3277"><a href="#3277">3277</a></td></tr
><tr id="gr_svn7768_3278"

><td id="3278"><a href="#3278">3278</a></td></tr
><tr id="gr_svn7768_3279"

><td id="3279"><a href="#3279">3279</a></td></tr
><tr id="gr_svn7768_3280"

><td id="3280"><a href="#3280">3280</a></td></tr
><tr id="gr_svn7768_3281"

><td id="3281"><a href="#3281">3281</a></td></tr
><tr id="gr_svn7768_3282"

><td id="3282"><a href="#3282">3282</a></td></tr
><tr id="gr_svn7768_3283"

><td id="3283"><a href="#3283">3283</a></td></tr
><tr id="gr_svn7768_3284"

><td id="3284"><a href="#3284">3284</a></td></tr
><tr id="gr_svn7768_3285"

><td id="3285"><a href="#3285">3285</a></td></tr
><tr id="gr_svn7768_3286"

><td id="3286"><a href="#3286">3286</a></td></tr
><tr id="gr_svn7768_3287"

><td id="3287"><a href="#3287">3287</a></td></tr
><tr id="gr_svn7768_3288"

><td id="3288"><a href="#3288">3288</a></td></tr
><tr id="gr_svn7768_3289"

><td id="3289"><a href="#3289">3289</a></td></tr
><tr id="gr_svn7768_3290"

><td id="3290"><a href="#3290">3290</a></td></tr
><tr id="gr_svn7768_3291"

><td id="3291"><a href="#3291">3291</a></td></tr
><tr id="gr_svn7768_3292"

><td id="3292"><a href="#3292">3292</a></td></tr
><tr id="gr_svn7768_3293"

><td id="3293"><a href="#3293">3293</a></td></tr
><tr id="gr_svn7768_3294"

><td id="3294"><a href="#3294">3294</a></td></tr
><tr id="gr_svn7768_3295"

><td id="3295"><a href="#3295">3295</a></td></tr
><tr id="gr_svn7768_3296"

><td id="3296"><a href="#3296">3296</a></td></tr
><tr id="gr_svn7768_3297"

><td id="3297"><a href="#3297">3297</a></td></tr
><tr id="gr_svn7768_3298"

><td id="3298"><a href="#3298">3298</a></td></tr
><tr id="gr_svn7768_3299"

><td id="3299"><a href="#3299">3299</a></td></tr
><tr id="gr_svn7768_3300"

><td id="3300"><a href="#3300">3300</a></td></tr
><tr id="gr_svn7768_3301"

><td id="3301"><a href="#3301">3301</a></td></tr
><tr id="gr_svn7768_3302"

><td id="3302"><a href="#3302">3302</a></td></tr
><tr id="gr_svn7768_3303"

><td id="3303"><a href="#3303">3303</a></td></tr
><tr id="gr_svn7768_3304"

><td id="3304"><a href="#3304">3304</a></td></tr
><tr id="gr_svn7768_3305"

><td id="3305"><a href="#3305">3305</a></td></tr
><tr id="gr_svn7768_3306"

><td id="3306"><a href="#3306">3306</a></td></tr
><tr id="gr_svn7768_3307"

><td id="3307"><a href="#3307">3307</a></td></tr
><tr id="gr_svn7768_3308"

><td id="3308"><a href="#3308">3308</a></td></tr
><tr id="gr_svn7768_3309"

><td id="3309"><a href="#3309">3309</a></td></tr
><tr id="gr_svn7768_3310"

><td id="3310"><a href="#3310">3310</a></td></tr
><tr id="gr_svn7768_3311"

><td id="3311"><a href="#3311">3311</a></td></tr
><tr id="gr_svn7768_3312"

><td id="3312"><a href="#3312">3312</a></td></tr
><tr id="gr_svn7768_3313"

><td id="3313"><a href="#3313">3313</a></td></tr
><tr id="gr_svn7768_3314"

><td id="3314"><a href="#3314">3314</a></td></tr
><tr id="gr_svn7768_3315"

><td id="3315"><a href="#3315">3315</a></td></tr
><tr id="gr_svn7768_3316"

><td id="3316"><a href="#3316">3316</a></td></tr
><tr id="gr_svn7768_3317"

><td id="3317"><a href="#3317">3317</a></td></tr
><tr id="gr_svn7768_3318"

><td id="3318"><a href="#3318">3318</a></td></tr
><tr id="gr_svn7768_3319"

><td id="3319"><a href="#3319">3319</a></td></tr
><tr id="gr_svn7768_3320"

><td id="3320"><a href="#3320">3320</a></td></tr
><tr id="gr_svn7768_3321"

><td id="3321"><a href="#3321">3321</a></td></tr
><tr id="gr_svn7768_3322"

><td id="3322"><a href="#3322">3322</a></td></tr
><tr id="gr_svn7768_3323"

><td id="3323"><a href="#3323">3323</a></td></tr
><tr id="gr_svn7768_3324"

><td id="3324"><a href="#3324">3324</a></td></tr
><tr id="gr_svn7768_3325"

><td id="3325"><a href="#3325">3325</a></td></tr
><tr id="gr_svn7768_3326"

><td id="3326"><a href="#3326">3326</a></td></tr
><tr id="gr_svn7768_3327"

><td id="3327"><a href="#3327">3327</a></td></tr
><tr id="gr_svn7768_3328"

><td id="3328"><a href="#3328">3328</a></td></tr
><tr id="gr_svn7768_3329"

><td id="3329"><a href="#3329">3329</a></td></tr
><tr id="gr_svn7768_3330"

><td id="3330"><a href="#3330">3330</a></td></tr
><tr id="gr_svn7768_3331"

><td id="3331"><a href="#3331">3331</a></td></tr
><tr id="gr_svn7768_3332"

><td id="3332"><a href="#3332">3332</a></td></tr
><tr id="gr_svn7768_3333"

><td id="3333"><a href="#3333">3333</a></td></tr
><tr id="gr_svn7768_3334"

><td id="3334"><a href="#3334">3334</a></td></tr
><tr id="gr_svn7768_3335"

><td id="3335"><a href="#3335">3335</a></td></tr
><tr id="gr_svn7768_3336"

><td id="3336"><a href="#3336">3336</a></td></tr
><tr id="gr_svn7768_3337"

><td id="3337"><a href="#3337">3337</a></td></tr
><tr id="gr_svn7768_3338"

><td id="3338"><a href="#3338">3338</a></td></tr
><tr id="gr_svn7768_3339"

><td id="3339"><a href="#3339">3339</a></td></tr
><tr id="gr_svn7768_3340"

><td id="3340"><a href="#3340">3340</a></td></tr
><tr id="gr_svn7768_3341"

><td id="3341"><a href="#3341">3341</a></td></tr
><tr id="gr_svn7768_3342"

><td id="3342"><a href="#3342">3342</a></td></tr
><tr id="gr_svn7768_3343"

><td id="3343"><a href="#3343">3343</a></td></tr
><tr id="gr_svn7768_3344"

><td id="3344"><a href="#3344">3344</a></td></tr
><tr id="gr_svn7768_3345"

><td id="3345"><a href="#3345">3345</a></td></tr
><tr id="gr_svn7768_3346"

><td id="3346"><a href="#3346">3346</a></td></tr
><tr id="gr_svn7768_3347"

><td id="3347"><a href="#3347">3347</a></td></tr
><tr id="gr_svn7768_3348"

><td id="3348"><a href="#3348">3348</a></td></tr
><tr id="gr_svn7768_3349"

><td id="3349"><a href="#3349">3349</a></td></tr
><tr id="gr_svn7768_3350"

><td id="3350"><a href="#3350">3350</a></td></tr
><tr id="gr_svn7768_3351"

><td id="3351"><a href="#3351">3351</a></td></tr
><tr id="gr_svn7768_3352"

><td id="3352"><a href="#3352">3352</a></td></tr
><tr id="gr_svn7768_3353"

><td id="3353"><a href="#3353">3353</a></td></tr
><tr id="gr_svn7768_3354"

><td id="3354"><a href="#3354">3354</a></td></tr
><tr id="gr_svn7768_3355"

><td id="3355"><a href="#3355">3355</a></td></tr
><tr id="gr_svn7768_3356"

><td id="3356"><a href="#3356">3356</a></td></tr
><tr id="gr_svn7768_3357"

><td id="3357"><a href="#3357">3357</a></td></tr
><tr id="gr_svn7768_3358"

><td id="3358"><a href="#3358">3358</a></td></tr
><tr id="gr_svn7768_3359"

><td id="3359"><a href="#3359">3359</a></td></tr
><tr id="gr_svn7768_3360"

><td id="3360"><a href="#3360">3360</a></td></tr
><tr id="gr_svn7768_3361"

><td id="3361"><a href="#3361">3361</a></td></tr
><tr id="gr_svn7768_3362"

><td id="3362"><a href="#3362">3362</a></td></tr
><tr id="gr_svn7768_3363"

><td id="3363"><a href="#3363">3363</a></td></tr
><tr id="gr_svn7768_3364"

><td id="3364"><a href="#3364">3364</a></td></tr
><tr id="gr_svn7768_3365"

><td id="3365"><a href="#3365">3365</a></td></tr
><tr id="gr_svn7768_3366"

><td id="3366"><a href="#3366">3366</a></td></tr
><tr id="gr_svn7768_3367"

><td id="3367"><a href="#3367">3367</a></td></tr
><tr id="gr_svn7768_3368"

><td id="3368"><a href="#3368">3368</a></td></tr
><tr id="gr_svn7768_3369"

><td id="3369"><a href="#3369">3369</a></td></tr
><tr id="gr_svn7768_3370"

><td id="3370"><a href="#3370">3370</a></td></tr
><tr id="gr_svn7768_3371"

><td id="3371"><a href="#3371">3371</a></td></tr
><tr id="gr_svn7768_3372"

><td id="3372"><a href="#3372">3372</a></td></tr
><tr id="gr_svn7768_3373"

><td id="3373"><a href="#3373">3373</a></td></tr
><tr id="gr_svn7768_3374"

><td id="3374"><a href="#3374">3374</a></td></tr
><tr id="gr_svn7768_3375"

><td id="3375"><a href="#3375">3375</a></td></tr
><tr id="gr_svn7768_3376"

><td id="3376"><a href="#3376">3376</a></td></tr
><tr id="gr_svn7768_3377"

><td id="3377"><a href="#3377">3377</a></td></tr
><tr id="gr_svn7768_3378"

><td id="3378"><a href="#3378">3378</a></td></tr
><tr id="gr_svn7768_3379"

><td id="3379"><a href="#3379">3379</a></td></tr
><tr id="gr_svn7768_3380"

><td id="3380"><a href="#3380">3380</a></td></tr
><tr id="gr_svn7768_3381"

><td id="3381"><a href="#3381">3381</a></td></tr
><tr id="gr_svn7768_3382"

><td id="3382"><a href="#3382">3382</a></td></tr
><tr id="gr_svn7768_3383"

><td id="3383"><a href="#3383">3383</a></td></tr
><tr id="gr_svn7768_3384"

><td id="3384"><a href="#3384">3384</a></td></tr
><tr id="gr_svn7768_3385"

><td id="3385"><a href="#3385">3385</a></td></tr
><tr id="gr_svn7768_3386"

><td id="3386"><a href="#3386">3386</a></td></tr
><tr id="gr_svn7768_3387"

><td id="3387"><a href="#3387">3387</a></td></tr
><tr id="gr_svn7768_3388"

><td id="3388"><a href="#3388">3388</a></td></tr
><tr id="gr_svn7768_3389"

><td id="3389"><a href="#3389">3389</a></td></tr
><tr id="gr_svn7768_3390"

><td id="3390"><a href="#3390">3390</a></td></tr
><tr id="gr_svn7768_3391"

><td id="3391"><a href="#3391">3391</a></td></tr
><tr id="gr_svn7768_3392"

><td id="3392"><a href="#3392">3392</a></td></tr
><tr id="gr_svn7768_3393"

><td id="3393"><a href="#3393">3393</a></td></tr
><tr id="gr_svn7768_3394"

><td id="3394"><a href="#3394">3394</a></td></tr
><tr id="gr_svn7768_3395"

><td id="3395"><a href="#3395">3395</a></td></tr
><tr id="gr_svn7768_3396"

><td id="3396"><a href="#3396">3396</a></td></tr
><tr id="gr_svn7768_3397"

><td id="3397"><a href="#3397">3397</a></td></tr
><tr id="gr_svn7768_3398"

><td id="3398"><a href="#3398">3398</a></td></tr
><tr id="gr_svn7768_3399"

><td id="3399"><a href="#3399">3399</a></td></tr
><tr id="gr_svn7768_3400"

><td id="3400"><a href="#3400">3400</a></td></tr
><tr id="gr_svn7768_3401"

><td id="3401"><a href="#3401">3401</a></td></tr
><tr id="gr_svn7768_3402"

><td id="3402"><a href="#3402">3402</a></td></tr
><tr id="gr_svn7768_3403"

><td id="3403"><a href="#3403">3403</a></td></tr
><tr id="gr_svn7768_3404"

><td id="3404"><a href="#3404">3404</a></td></tr
><tr id="gr_svn7768_3405"

><td id="3405"><a href="#3405">3405</a></td></tr
><tr id="gr_svn7768_3406"

><td id="3406"><a href="#3406">3406</a></td></tr
><tr id="gr_svn7768_3407"

><td id="3407"><a href="#3407">3407</a></td></tr
><tr id="gr_svn7768_3408"

><td id="3408"><a href="#3408">3408</a></td></tr
><tr id="gr_svn7768_3409"

><td id="3409"><a href="#3409">3409</a></td></tr
><tr id="gr_svn7768_3410"

><td id="3410"><a href="#3410">3410</a></td></tr
><tr id="gr_svn7768_3411"

><td id="3411"><a href="#3411">3411</a></td></tr
><tr id="gr_svn7768_3412"

><td id="3412"><a href="#3412">3412</a></td></tr
><tr id="gr_svn7768_3413"

><td id="3413"><a href="#3413">3413</a></td></tr
><tr id="gr_svn7768_3414"

><td id="3414"><a href="#3414">3414</a></td></tr
><tr id="gr_svn7768_3415"

><td id="3415"><a href="#3415">3415</a></td></tr
><tr id="gr_svn7768_3416"

><td id="3416"><a href="#3416">3416</a></td></tr
><tr id="gr_svn7768_3417"

><td id="3417"><a href="#3417">3417</a></td></tr
><tr id="gr_svn7768_3418"

><td id="3418"><a href="#3418">3418</a></td></tr
><tr id="gr_svn7768_3419"

><td id="3419"><a href="#3419">3419</a></td></tr
><tr id="gr_svn7768_3420"

><td id="3420"><a href="#3420">3420</a></td></tr
><tr id="gr_svn7768_3421"

><td id="3421"><a href="#3421">3421</a></td></tr
><tr id="gr_svn7768_3422"

><td id="3422"><a href="#3422">3422</a></td></tr
><tr id="gr_svn7768_3423"

><td id="3423"><a href="#3423">3423</a></td></tr
><tr id="gr_svn7768_3424"

><td id="3424"><a href="#3424">3424</a></td></tr
><tr id="gr_svn7768_3425"

><td id="3425"><a href="#3425">3425</a></td></tr
><tr id="gr_svn7768_3426"

><td id="3426"><a href="#3426">3426</a></td></tr
><tr id="gr_svn7768_3427"

><td id="3427"><a href="#3427">3427</a></td></tr
><tr id="gr_svn7768_3428"

><td id="3428"><a href="#3428">3428</a></td></tr
><tr id="gr_svn7768_3429"

><td id="3429"><a href="#3429">3429</a></td></tr
><tr id="gr_svn7768_3430"

><td id="3430"><a href="#3430">3430</a></td></tr
><tr id="gr_svn7768_3431"

><td id="3431"><a href="#3431">3431</a></td></tr
><tr id="gr_svn7768_3432"

><td id="3432"><a href="#3432">3432</a></td></tr
><tr id="gr_svn7768_3433"

><td id="3433"><a href="#3433">3433</a></td></tr
><tr id="gr_svn7768_3434"

><td id="3434"><a href="#3434">3434</a></td></tr
><tr id="gr_svn7768_3435"

><td id="3435"><a href="#3435">3435</a></td></tr
><tr id="gr_svn7768_3436"

><td id="3436"><a href="#3436">3436</a></td></tr
><tr id="gr_svn7768_3437"

><td id="3437"><a href="#3437">3437</a></td></tr
><tr id="gr_svn7768_3438"

><td id="3438"><a href="#3438">3438</a></td></tr
><tr id="gr_svn7768_3439"

><td id="3439"><a href="#3439">3439</a></td></tr
><tr id="gr_svn7768_3440"

><td id="3440"><a href="#3440">3440</a></td></tr
><tr id="gr_svn7768_3441"

><td id="3441"><a href="#3441">3441</a></td></tr
><tr id="gr_svn7768_3442"

><td id="3442"><a href="#3442">3442</a></td></tr
><tr id="gr_svn7768_3443"

><td id="3443"><a href="#3443">3443</a></td></tr
><tr id="gr_svn7768_3444"

><td id="3444"><a href="#3444">3444</a></td></tr
><tr id="gr_svn7768_3445"

><td id="3445"><a href="#3445">3445</a></td></tr
><tr id="gr_svn7768_3446"

><td id="3446"><a href="#3446">3446</a></td></tr
><tr id="gr_svn7768_3447"

><td id="3447"><a href="#3447">3447</a></td></tr
><tr id="gr_svn7768_3448"

><td id="3448"><a href="#3448">3448</a></td></tr
><tr id="gr_svn7768_3449"

><td id="3449"><a href="#3449">3449</a></td></tr
><tr id="gr_svn7768_3450"

><td id="3450"><a href="#3450">3450</a></td></tr
><tr id="gr_svn7768_3451"

><td id="3451"><a href="#3451">3451</a></td></tr
><tr id="gr_svn7768_3452"

><td id="3452"><a href="#3452">3452</a></td></tr
><tr id="gr_svn7768_3453"

><td id="3453"><a href="#3453">3453</a></td></tr
><tr id="gr_svn7768_3454"

><td id="3454"><a href="#3454">3454</a></td></tr
><tr id="gr_svn7768_3455"

><td id="3455"><a href="#3455">3455</a></td></tr
><tr id="gr_svn7768_3456"

><td id="3456"><a href="#3456">3456</a></td></tr
><tr id="gr_svn7768_3457"

><td id="3457"><a href="#3457">3457</a></td></tr
><tr id="gr_svn7768_3458"

><td id="3458"><a href="#3458">3458</a></td></tr
><tr id="gr_svn7768_3459"

><td id="3459"><a href="#3459">3459</a></td></tr
><tr id="gr_svn7768_3460"

><td id="3460"><a href="#3460">3460</a></td></tr
><tr id="gr_svn7768_3461"

><td id="3461"><a href="#3461">3461</a></td></tr
><tr id="gr_svn7768_3462"

><td id="3462"><a href="#3462">3462</a></td></tr
><tr id="gr_svn7768_3463"

><td id="3463"><a href="#3463">3463</a></td></tr
><tr id="gr_svn7768_3464"

><td id="3464"><a href="#3464">3464</a></td></tr
><tr id="gr_svn7768_3465"

><td id="3465"><a href="#3465">3465</a></td></tr
><tr id="gr_svn7768_3466"

><td id="3466"><a href="#3466">3466</a></td></tr
><tr id="gr_svn7768_3467"

><td id="3467"><a href="#3467">3467</a></td></tr
><tr id="gr_svn7768_3468"

><td id="3468"><a href="#3468">3468</a></td></tr
><tr id="gr_svn7768_3469"

><td id="3469"><a href="#3469">3469</a></td></tr
><tr id="gr_svn7768_3470"

><td id="3470"><a href="#3470">3470</a></td></tr
><tr id="gr_svn7768_3471"

><td id="3471"><a href="#3471">3471</a></td></tr
><tr id="gr_svn7768_3472"

><td id="3472"><a href="#3472">3472</a></td></tr
><tr id="gr_svn7768_3473"

><td id="3473"><a href="#3473">3473</a></td></tr
><tr id="gr_svn7768_3474"

><td id="3474"><a href="#3474">3474</a></td></tr
><tr id="gr_svn7768_3475"

><td id="3475"><a href="#3475">3475</a></td></tr
><tr id="gr_svn7768_3476"

><td id="3476"><a href="#3476">3476</a></td></tr
><tr id="gr_svn7768_3477"

><td id="3477"><a href="#3477">3477</a></td></tr
><tr id="gr_svn7768_3478"

><td id="3478"><a href="#3478">3478</a></td></tr
><tr id="gr_svn7768_3479"

><td id="3479"><a href="#3479">3479</a></td></tr
><tr id="gr_svn7768_3480"

><td id="3480"><a href="#3480">3480</a></td></tr
><tr id="gr_svn7768_3481"

><td id="3481"><a href="#3481">3481</a></td></tr
><tr id="gr_svn7768_3482"

><td id="3482"><a href="#3482">3482</a></td></tr
><tr id="gr_svn7768_3483"

><td id="3483"><a href="#3483">3483</a></td></tr
><tr id="gr_svn7768_3484"

><td id="3484"><a href="#3484">3484</a></td></tr
><tr id="gr_svn7768_3485"

><td id="3485"><a href="#3485">3485</a></td></tr
><tr id="gr_svn7768_3486"

><td id="3486"><a href="#3486">3486</a></td></tr
><tr id="gr_svn7768_3487"

><td id="3487"><a href="#3487">3487</a></td></tr
><tr id="gr_svn7768_3488"

><td id="3488"><a href="#3488">3488</a></td></tr
><tr id="gr_svn7768_3489"

><td id="3489"><a href="#3489">3489</a></td></tr
><tr id="gr_svn7768_3490"

><td id="3490"><a href="#3490">3490</a></td></tr
><tr id="gr_svn7768_3491"

><td id="3491"><a href="#3491">3491</a></td></tr
><tr id="gr_svn7768_3492"

><td id="3492"><a href="#3492">3492</a></td></tr
><tr id="gr_svn7768_3493"

><td id="3493"><a href="#3493">3493</a></td></tr
><tr id="gr_svn7768_3494"

><td id="3494"><a href="#3494">3494</a></td></tr
><tr id="gr_svn7768_3495"

><td id="3495"><a href="#3495">3495</a></td></tr
><tr id="gr_svn7768_3496"

><td id="3496"><a href="#3496">3496</a></td></tr
><tr id="gr_svn7768_3497"

><td id="3497"><a href="#3497">3497</a></td></tr
><tr id="gr_svn7768_3498"

><td id="3498"><a href="#3498">3498</a></td></tr
><tr id="gr_svn7768_3499"

><td id="3499"><a href="#3499">3499</a></td></tr
><tr id="gr_svn7768_3500"

><td id="3500"><a href="#3500">3500</a></td></tr
><tr id="gr_svn7768_3501"

><td id="3501"><a href="#3501">3501</a></td></tr
><tr id="gr_svn7768_3502"

><td id="3502"><a href="#3502">3502</a></td></tr
><tr id="gr_svn7768_3503"

><td id="3503"><a href="#3503">3503</a></td></tr
><tr id="gr_svn7768_3504"

><td id="3504"><a href="#3504">3504</a></td></tr
><tr id="gr_svn7768_3505"

><td id="3505"><a href="#3505">3505</a></td></tr
><tr id="gr_svn7768_3506"

><td id="3506"><a href="#3506">3506</a></td></tr
><tr id="gr_svn7768_3507"

><td id="3507"><a href="#3507">3507</a></td></tr
><tr id="gr_svn7768_3508"

><td id="3508"><a href="#3508">3508</a></td></tr
><tr id="gr_svn7768_3509"

><td id="3509"><a href="#3509">3509</a></td></tr
><tr id="gr_svn7768_3510"

><td id="3510"><a href="#3510">3510</a></td></tr
><tr id="gr_svn7768_3511"

><td id="3511"><a href="#3511">3511</a></td></tr
><tr id="gr_svn7768_3512"

><td id="3512"><a href="#3512">3512</a></td></tr
><tr id="gr_svn7768_3513"

><td id="3513"><a href="#3513">3513</a></td></tr
><tr id="gr_svn7768_3514"

><td id="3514"><a href="#3514">3514</a></td></tr
><tr id="gr_svn7768_3515"

><td id="3515"><a href="#3515">3515</a></td></tr
><tr id="gr_svn7768_3516"

><td id="3516"><a href="#3516">3516</a></td></tr
><tr id="gr_svn7768_3517"

><td id="3517"><a href="#3517">3517</a></td></tr
><tr id="gr_svn7768_3518"

><td id="3518"><a href="#3518">3518</a></td></tr
><tr id="gr_svn7768_3519"

><td id="3519"><a href="#3519">3519</a></td></tr
><tr id="gr_svn7768_3520"

><td id="3520"><a href="#3520">3520</a></td></tr
><tr id="gr_svn7768_3521"

><td id="3521"><a href="#3521">3521</a></td></tr
><tr id="gr_svn7768_3522"

><td id="3522"><a href="#3522">3522</a></td></tr
><tr id="gr_svn7768_3523"

><td id="3523"><a href="#3523">3523</a></td></tr
><tr id="gr_svn7768_3524"

><td id="3524"><a href="#3524">3524</a></td></tr
><tr id="gr_svn7768_3525"

><td id="3525"><a href="#3525">3525</a></td></tr
><tr id="gr_svn7768_3526"

><td id="3526"><a href="#3526">3526</a></td></tr
><tr id="gr_svn7768_3527"

><td id="3527"><a href="#3527">3527</a></td></tr
><tr id="gr_svn7768_3528"

><td id="3528"><a href="#3528">3528</a></td></tr
><tr id="gr_svn7768_3529"

><td id="3529"><a href="#3529">3529</a></td></tr
><tr id="gr_svn7768_3530"

><td id="3530"><a href="#3530">3530</a></td></tr
><tr id="gr_svn7768_3531"

><td id="3531"><a href="#3531">3531</a></td></tr
><tr id="gr_svn7768_3532"

><td id="3532"><a href="#3532">3532</a></td></tr
><tr id="gr_svn7768_3533"

><td id="3533"><a href="#3533">3533</a></td></tr
><tr id="gr_svn7768_3534"

><td id="3534"><a href="#3534">3534</a></td></tr
><tr id="gr_svn7768_3535"

><td id="3535"><a href="#3535">3535</a></td></tr
><tr id="gr_svn7768_3536"

><td id="3536"><a href="#3536">3536</a></td></tr
><tr id="gr_svn7768_3537"

><td id="3537"><a href="#3537">3537</a></td></tr
><tr id="gr_svn7768_3538"

><td id="3538"><a href="#3538">3538</a></td></tr
><tr id="gr_svn7768_3539"

><td id="3539"><a href="#3539">3539</a></td></tr
><tr id="gr_svn7768_3540"

><td id="3540"><a href="#3540">3540</a></td></tr
><tr id="gr_svn7768_3541"

><td id="3541"><a href="#3541">3541</a></td></tr
><tr id="gr_svn7768_3542"

><td id="3542"><a href="#3542">3542</a></td></tr
><tr id="gr_svn7768_3543"

><td id="3543"><a href="#3543">3543</a></td></tr
><tr id="gr_svn7768_3544"

><td id="3544"><a href="#3544">3544</a></td></tr
><tr id="gr_svn7768_3545"

><td id="3545"><a href="#3545">3545</a></td></tr
><tr id="gr_svn7768_3546"

><td id="3546"><a href="#3546">3546</a></td></tr
><tr id="gr_svn7768_3547"

><td id="3547"><a href="#3547">3547</a></td></tr
><tr id="gr_svn7768_3548"

><td id="3548"><a href="#3548">3548</a></td></tr
><tr id="gr_svn7768_3549"

><td id="3549"><a href="#3549">3549</a></td></tr
><tr id="gr_svn7768_3550"

><td id="3550"><a href="#3550">3550</a></td></tr
><tr id="gr_svn7768_3551"

><td id="3551"><a href="#3551">3551</a></td></tr
><tr id="gr_svn7768_3552"

><td id="3552"><a href="#3552">3552</a></td></tr
><tr id="gr_svn7768_3553"

><td id="3553"><a href="#3553">3553</a></td></tr
><tr id="gr_svn7768_3554"

><td id="3554"><a href="#3554">3554</a></td></tr
><tr id="gr_svn7768_3555"

><td id="3555"><a href="#3555">3555</a></td></tr
><tr id="gr_svn7768_3556"

><td id="3556"><a href="#3556">3556</a></td></tr
><tr id="gr_svn7768_3557"

><td id="3557"><a href="#3557">3557</a></td></tr
><tr id="gr_svn7768_3558"

><td id="3558"><a href="#3558">3558</a></td></tr
><tr id="gr_svn7768_3559"

><td id="3559"><a href="#3559">3559</a></td></tr
><tr id="gr_svn7768_3560"

><td id="3560"><a href="#3560">3560</a></td></tr
><tr id="gr_svn7768_3561"

><td id="3561"><a href="#3561">3561</a></td></tr
><tr id="gr_svn7768_3562"

><td id="3562"><a href="#3562">3562</a></td></tr
><tr id="gr_svn7768_3563"

><td id="3563"><a href="#3563">3563</a></td></tr
><tr id="gr_svn7768_3564"

><td id="3564"><a href="#3564">3564</a></td></tr
><tr id="gr_svn7768_3565"

><td id="3565"><a href="#3565">3565</a></td></tr
><tr id="gr_svn7768_3566"

><td id="3566"><a href="#3566">3566</a></td></tr
><tr id="gr_svn7768_3567"

><td id="3567"><a href="#3567">3567</a></td></tr
><tr id="gr_svn7768_3568"

><td id="3568"><a href="#3568">3568</a></td></tr
><tr id="gr_svn7768_3569"

><td id="3569"><a href="#3569">3569</a></td></tr
><tr id="gr_svn7768_3570"

><td id="3570"><a href="#3570">3570</a></td></tr
><tr id="gr_svn7768_3571"

><td id="3571"><a href="#3571">3571</a></td></tr
><tr id="gr_svn7768_3572"

><td id="3572"><a href="#3572">3572</a></td></tr
><tr id="gr_svn7768_3573"

><td id="3573"><a href="#3573">3573</a></td></tr
><tr id="gr_svn7768_3574"

><td id="3574"><a href="#3574">3574</a></td></tr
><tr id="gr_svn7768_3575"

><td id="3575"><a href="#3575">3575</a></td></tr
><tr id="gr_svn7768_3576"

><td id="3576"><a href="#3576">3576</a></td></tr
><tr id="gr_svn7768_3577"

><td id="3577"><a href="#3577">3577</a></td></tr
><tr id="gr_svn7768_3578"

><td id="3578"><a href="#3578">3578</a></td></tr
><tr id="gr_svn7768_3579"

><td id="3579"><a href="#3579">3579</a></td></tr
><tr id="gr_svn7768_3580"

><td id="3580"><a href="#3580">3580</a></td></tr
><tr id="gr_svn7768_3581"

><td id="3581"><a href="#3581">3581</a></td></tr
><tr id="gr_svn7768_3582"

><td id="3582"><a href="#3582">3582</a></td></tr
><tr id="gr_svn7768_3583"

><td id="3583"><a href="#3583">3583</a></td></tr
><tr id="gr_svn7768_3584"

><td id="3584"><a href="#3584">3584</a></td></tr
><tr id="gr_svn7768_3585"

><td id="3585"><a href="#3585">3585</a></td></tr
><tr id="gr_svn7768_3586"

><td id="3586"><a href="#3586">3586</a></td></tr
><tr id="gr_svn7768_3587"

><td id="3587"><a href="#3587">3587</a></td></tr
><tr id="gr_svn7768_3588"

><td id="3588"><a href="#3588">3588</a></td></tr
><tr id="gr_svn7768_3589"

><td id="3589"><a href="#3589">3589</a></td></tr
><tr id="gr_svn7768_3590"

><td id="3590"><a href="#3590">3590</a></td></tr
><tr id="gr_svn7768_3591"

><td id="3591"><a href="#3591">3591</a></td></tr
><tr id="gr_svn7768_3592"

><td id="3592"><a href="#3592">3592</a></td></tr
><tr id="gr_svn7768_3593"

><td id="3593"><a href="#3593">3593</a></td></tr
><tr id="gr_svn7768_3594"

><td id="3594"><a href="#3594">3594</a></td></tr
><tr id="gr_svn7768_3595"

><td id="3595"><a href="#3595">3595</a></td></tr
><tr id="gr_svn7768_3596"

><td id="3596"><a href="#3596">3596</a></td></tr
><tr id="gr_svn7768_3597"

><td id="3597"><a href="#3597">3597</a></td></tr
><tr id="gr_svn7768_3598"

><td id="3598"><a href="#3598">3598</a></td></tr
><tr id="gr_svn7768_3599"

><td id="3599"><a href="#3599">3599</a></td></tr
><tr id="gr_svn7768_3600"

><td id="3600"><a href="#3600">3600</a></td></tr
><tr id="gr_svn7768_3601"

><td id="3601"><a href="#3601">3601</a></td></tr
><tr id="gr_svn7768_3602"

><td id="3602"><a href="#3602">3602</a></td></tr
><tr id="gr_svn7768_3603"

><td id="3603"><a href="#3603">3603</a></td></tr
><tr id="gr_svn7768_3604"

><td id="3604"><a href="#3604">3604</a></td></tr
><tr id="gr_svn7768_3605"

><td id="3605"><a href="#3605">3605</a></td></tr
><tr id="gr_svn7768_3606"

><td id="3606"><a href="#3606">3606</a></td></tr
><tr id="gr_svn7768_3607"

><td id="3607"><a href="#3607">3607</a></td></tr
><tr id="gr_svn7768_3608"

><td id="3608"><a href="#3608">3608</a></td></tr
><tr id="gr_svn7768_3609"

><td id="3609"><a href="#3609">3609</a></td></tr
><tr id="gr_svn7768_3610"

><td id="3610"><a href="#3610">3610</a></td></tr
><tr id="gr_svn7768_3611"

><td id="3611"><a href="#3611">3611</a></td></tr
><tr id="gr_svn7768_3612"

><td id="3612"><a href="#3612">3612</a></td></tr
><tr id="gr_svn7768_3613"

><td id="3613"><a href="#3613">3613</a></td></tr
><tr id="gr_svn7768_3614"

><td id="3614"><a href="#3614">3614</a></td></tr
><tr id="gr_svn7768_3615"

><td id="3615"><a href="#3615">3615</a></td></tr
><tr id="gr_svn7768_3616"

><td id="3616"><a href="#3616">3616</a></td></tr
><tr id="gr_svn7768_3617"

><td id="3617"><a href="#3617">3617</a></td></tr
><tr id="gr_svn7768_3618"

><td id="3618"><a href="#3618">3618</a></td></tr
><tr id="gr_svn7768_3619"

><td id="3619"><a href="#3619">3619</a></td></tr
><tr id="gr_svn7768_3620"

><td id="3620"><a href="#3620">3620</a></td></tr
><tr id="gr_svn7768_3621"

><td id="3621"><a href="#3621">3621</a></td></tr
><tr id="gr_svn7768_3622"

><td id="3622"><a href="#3622">3622</a></td></tr
><tr id="gr_svn7768_3623"

><td id="3623"><a href="#3623">3623</a></td></tr
><tr id="gr_svn7768_3624"

><td id="3624"><a href="#3624">3624</a></td></tr
><tr id="gr_svn7768_3625"

><td id="3625"><a href="#3625">3625</a></td></tr
><tr id="gr_svn7768_3626"

><td id="3626"><a href="#3626">3626</a></td></tr
><tr id="gr_svn7768_3627"

><td id="3627"><a href="#3627">3627</a></td></tr
><tr id="gr_svn7768_3628"

><td id="3628"><a href="#3628">3628</a></td></tr
><tr id="gr_svn7768_3629"

><td id="3629"><a href="#3629">3629</a></td></tr
><tr id="gr_svn7768_3630"

><td id="3630"><a href="#3630">3630</a></td></tr
><tr id="gr_svn7768_3631"

><td id="3631"><a href="#3631">3631</a></td></tr
><tr id="gr_svn7768_3632"

><td id="3632"><a href="#3632">3632</a></td></tr
><tr id="gr_svn7768_3633"

><td id="3633"><a href="#3633">3633</a></td></tr
><tr id="gr_svn7768_3634"

><td id="3634"><a href="#3634">3634</a></td></tr
><tr id="gr_svn7768_3635"

><td id="3635"><a href="#3635">3635</a></td></tr
><tr id="gr_svn7768_3636"

><td id="3636"><a href="#3636">3636</a></td></tr
><tr id="gr_svn7768_3637"

><td id="3637"><a href="#3637">3637</a></td></tr
><tr id="gr_svn7768_3638"

><td id="3638"><a href="#3638">3638</a></td></tr
><tr id="gr_svn7768_3639"

><td id="3639"><a href="#3639">3639</a></td></tr
><tr id="gr_svn7768_3640"

><td id="3640"><a href="#3640">3640</a></td></tr
><tr id="gr_svn7768_3641"

><td id="3641"><a href="#3641">3641</a></td></tr
><tr id="gr_svn7768_3642"

><td id="3642"><a href="#3642">3642</a></td></tr
><tr id="gr_svn7768_3643"

><td id="3643"><a href="#3643">3643</a></td></tr
><tr id="gr_svn7768_3644"

><td id="3644"><a href="#3644">3644</a></td></tr
><tr id="gr_svn7768_3645"

><td id="3645"><a href="#3645">3645</a></td></tr
><tr id="gr_svn7768_3646"

><td id="3646"><a href="#3646">3646</a></td></tr
><tr id="gr_svn7768_3647"

><td id="3647"><a href="#3647">3647</a></td></tr
><tr id="gr_svn7768_3648"

><td id="3648"><a href="#3648">3648</a></td></tr
><tr id="gr_svn7768_3649"

><td id="3649"><a href="#3649">3649</a></td></tr
><tr id="gr_svn7768_3650"

><td id="3650"><a href="#3650">3650</a></td></tr
><tr id="gr_svn7768_3651"

><td id="3651"><a href="#3651">3651</a></td></tr
><tr id="gr_svn7768_3652"

><td id="3652"><a href="#3652">3652</a></td></tr
><tr id="gr_svn7768_3653"

><td id="3653"><a href="#3653">3653</a></td></tr
><tr id="gr_svn7768_3654"

><td id="3654"><a href="#3654">3654</a></td></tr
><tr id="gr_svn7768_3655"

><td id="3655"><a href="#3655">3655</a></td></tr
><tr id="gr_svn7768_3656"

><td id="3656"><a href="#3656">3656</a></td></tr
><tr id="gr_svn7768_3657"

><td id="3657"><a href="#3657">3657</a></td></tr
><tr id="gr_svn7768_3658"

><td id="3658"><a href="#3658">3658</a></td></tr
><tr id="gr_svn7768_3659"

><td id="3659"><a href="#3659">3659</a></td></tr
><tr id="gr_svn7768_3660"

><td id="3660"><a href="#3660">3660</a></td></tr
><tr id="gr_svn7768_3661"

><td id="3661"><a href="#3661">3661</a></td></tr
><tr id="gr_svn7768_3662"

><td id="3662"><a href="#3662">3662</a></td></tr
><tr id="gr_svn7768_3663"

><td id="3663"><a href="#3663">3663</a></td></tr
><tr id="gr_svn7768_3664"

><td id="3664"><a href="#3664">3664</a></td></tr
><tr id="gr_svn7768_3665"

><td id="3665"><a href="#3665">3665</a></td></tr
><tr id="gr_svn7768_3666"

><td id="3666"><a href="#3666">3666</a></td></tr
><tr id="gr_svn7768_3667"

><td id="3667"><a href="#3667">3667</a></td></tr
><tr id="gr_svn7768_3668"

><td id="3668"><a href="#3668">3668</a></td></tr
><tr id="gr_svn7768_3669"

><td id="3669"><a href="#3669">3669</a></td></tr
><tr id="gr_svn7768_3670"

><td id="3670"><a href="#3670">3670</a></td></tr
><tr id="gr_svn7768_3671"

><td id="3671"><a href="#3671">3671</a></td></tr
><tr id="gr_svn7768_3672"

><td id="3672"><a href="#3672">3672</a></td></tr
><tr id="gr_svn7768_3673"

><td id="3673"><a href="#3673">3673</a></td></tr
><tr id="gr_svn7768_3674"

><td id="3674"><a href="#3674">3674</a></td></tr
><tr id="gr_svn7768_3675"

><td id="3675"><a href="#3675">3675</a></td></tr
><tr id="gr_svn7768_3676"

><td id="3676"><a href="#3676">3676</a></td></tr
><tr id="gr_svn7768_3677"

><td id="3677"><a href="#3677">3677</a></td></tr
><tr id="gr_svn7768_3678"

><td id="3678"><a href="#3678">3678</a></td></tr
><tr id="gr_svn7768_3679"

><td id="3679"><a href="#3679">3679</a></td></tr
><tr id="gr_svn7768_3680"

><td id="3680"><a href="#3680">3680</a></td></tr
><tr id="gr_svn7768_3681"

><td id="3681"><a href="#3681">3681</a></td></tr
><tr id="gr_svn7768_3682"

><td id="3682"><a href="#3682">3682</a></td></tr
><tr id="gr_svn7768_3683"

><td id="3683"><a href="#3683">3683</a></td></tr
><tr id="gr_svn7768_3684"

><td id="3684"><a href="#3684">3684</a></td></tr
><tr id="gr_svn7768_3685"

><td id="3685"><a href="#3685">3685</a></td></tr
><tr id="gr_svn7768_3686"

><td id="3686"><a href="#3686">3686</a></td></tr
><tr id="gr_svn7768_3687"

><td id="3687"><a href="#3687">3687</a></td></tr
><tr id="gr_svn7768_3688"

><td id="3688"><a href="#3688">3688</a></td></tr
><tr id="gr_svn7768_3689"

><td id="3689"><a href="#3689">3689</a></td></tr
><tr id="gr_svn7768_3690"

><td id="3690"><a href="#3690">3690</a></td></tr
><tr id="gr_svn7768_3691"

><td id="3691"><a href="#3691">3691</a></td></tr
><tr id="gr_svn7768_3692"

><td id="3692"><a href="#3692">3692</a></td></tr
><tr id="gr_svn7768_3693"

><td id="3693"><a href="#3693">3693</a></td></tr
><tr id="gr_svn7768_3694"

><td id="3694"><a href="#3694">3694</a></td></tr
><tr id="gr_svn7768_3695"

><td id="3695"><a href="#3695">3695</a></td></tr
><tr id="gr_svn7768_3696"

><td id="3696"><a href="#3696">3696</a></td></tr
><tr id="gr_svn7768_3697"

><td id="3697"><a href="#3697">3697</a></td></tr
><tr id="gr_svn7768_3698"

><td id="3698"><a href="#3698">3698</a></td></tr
><tr id="gr_svn7768_3699"

><td id="3699"><a href="#3699">3699</a></td></tr
><tr id="gr_svn7768_3700"

><td id="3700"><a href="#3700">3700</a></td></tr
><tr id="gr_svn7768_3701"

><td id="3701"><a href="#3701">3701</a></td></tr
><tr id="gr_svn7768_3702"

><td id="3702"><a href="#3702">3702</a></td></tr
><tr id="gr_svn7768_3703"

><td id="3703"><a href="#3703">3703</a></td></tr
><tr id="gr_svn7768_3704"

><td id="3704"><a href="#3704">3704</a></td></tr
><tr id="gr_svn7768_3705"

><td id="3705"><a href="#3705">3705</a></td></tr
><tr id="gr_svn7768_3706"

><td id="3706"><a href="#3706">3706</a></td></tr
><tr id="gr_svn7768_3707"

><td id="3707"><a href="#3707">3707</a></td></tr
><tr id="gr_svn7768_3708"

><td id="3708"><a href="#3708">3708</a></td></tr
><tr id="gr_svn7768_3709"

><td id="3709"><a href="#3709">3709</a></td></tr
><tr id="gr_svn7768_3710"

><td id="3710"><a href="#3710">3710</a></td></tr
><tr id="gr_svn7768_3711"

><td id="3711"><a href="#3711">3711</a></td></tr
><tr id="gr_svn7768_3712"

><td id="3712"><a href="#3712">3712</a></td></tr
><tr id="gr_svn7768_3713"

><td id="3713"><a href="#3713">3713</a></td></tr
><tr id="gr_svn7768_3714"

><td id="3714"><a href="#3714">3714</a></td></tr
><tr id="gr_svn7768_3715"

><td id="3715"><a href="#3715">3715</a></td></tr
><tr id="gr_svn7768_3716"

><td id="3716"><a href="#3716">3716</a></td></tr
><tr id="gr_svn7768_3717"

><td id="3717"><a href="#3717">3717</a></td></tr
><tr id="gr_svn7768_3718"

><td id="3718"><a href="#3718">3718</a></td></tr
><tr id="gr_svn7768_3719"

><td id="3719"><a href="#3719">3719</a></td></tr
><tr id="gr_svn7768_3720"

><td id="3720"><a href="#3720">3720</a></td></tr
><tr id="gr_svn7768_3721"

><td id="3721"><a href="#3721">3721</a></td></tr
><tr id="gr_svn7768_3722"

><td id="3722"><a href="#3722">3722</a></td></tr
><tr id="gr_svn7768_3723"

><td id="3723"><a href="#3723">3723</a></td></tr
><tr id="gr_svn7768_3724"

><td id="3724"><a href="#3724">3724</a></td></tr
><tr id="gr_svn7768_3725"

><td id="3725"><a href="#3725">3725</a></td></tr
><tr id="gr_svn7768_3726"

><td id="3726"><a href="#3726">3726</a></td></tr
><tr id="gr_svn7768_3727"

><td id="3727"><a href="#3727">3727</a></td></tr
><tr id="gr_svn7768_3728"

><td id="3728"><a href="#3728">3728</a></td></tr
><tr id="gr_svn7768_3729"

><td id="3729"><a href="#3729">3729</a></td></tr
><tr id="gr_svn7768_3730"

><td id="3730"><a href="#3730">3730</a></td></tr
><tr id="gr_svn7768_3731"

><td id="3731"><a href="#3731">3731</a></td></tr
><tr id="gr_svn7768_3732"

><td id="3732"><a href="#3732">3732</a></td></tr
><tr id="gr_svn7768_3733"

><td id="3733"><a href="#3733">3733</a></td></tr
><tr id="gr_svn7768_3734"

><td id="3734"><a href="#3734">3734</a></td></tr
><tr id="gr_svn7768_3735"

><td id="3735"><a href="#3735">3735</a></td></tr
><tr id="gr_svn7768_3736"

><td id="3736"><a href="#3736">3736</a></td></tr
><tr id="gr_svn7768_3737"

><td id="3737"><a href="#3737">3737</a></td></tr
><tr id="gr_svn7768_3738"

><td id="3738"><a href="#3738">3738</a></td></tr
><tr id="gr_svn7768_3739"

><td id="3739"><a href="#3739">3739</a></td></tr
><tr id="gr_svn7768_3740"

><td id="3740"><a href="#3740">3740</a></td></tr
><tr id="gr_svn7768_3741"

><td id="3741"><a href="#3741">3741</a></td></tr
><tr id="gr_svn7768_3742"

><td id="3742"><a href="#3742">3742</a></td></tr
><tr id="gr_svn7768_3743"

><td id="3743"><a href="#3743">3743</a></td></tr
><tr id="gr_svn7768_3744"

><td id="3744"><a href="#3744">3744</a></td></tr
><tr id="gr_svn7768_3745"

><td id="3745"><a href="#3745">3745</a></td></tr
><tr id="gr_svn7768_3746"

><td id="3746"><a href="#3746">3746</a></td></tr
><tr id="gr_svn7768_3747"

><td id="3747"><a href="#3747">3747</a></td></tr
><tr id="gr_svn7768_3748"

><td id="3748"><a href="#3748">3748</a></td></tr
><tr id="gr_svn7768_3749"

><td id="3749"><a href="#3749">3749</a></td></tr
><tr id="gr_svn7768_3750"

><td id="3750"><a href="#3750">3750</a></td></tr
><tr id="gr_svn7768_3751"

><td id="3751"><a href="#3751">3751</a></td></tr
><tr id="gr_svn7768_3752"

><td id="3752"><a href="#3752">3752</a></td></tr
><tr id="gr_svn7768_3753"

><td id="3753"><a href="#3753">3753</a></td></tr
><tr id="gr_svn7768_3754"

><td id="3754"><a href="#3754">3754</a></td></tr
><tr id="gr_svn7768_3755"

><td id="3755"><a href="#3755">3755</a></td></tr
><tr id="gr_svn7768_3756"

><td id="3756"><a href="#3756">3756</a></td></tr
><tr id="gr_svn7768_3757"

><td id="3757"><a href="#3757">3757</a></td></tr
><tr id="gr_svn7768_3758"

><td id="3758"><a href="#3758">3758</a></td></tr
><tr id="gr_svn7768_3759"

><td id="3759"><a href="#3759">3759</a></td></tr
><tr id="gr_svn7768_3760"

><td id="3760"><a href="#3760">3760</a></td></tr
><tr id="gr_svn7768_3761"

><td id="3761"><a href="#3761">3761</a></td></tr
><tr id="gr_svn7768_3762"

><td id="3762"><a href="#3762">3762</a></td></tr
><tr id="gr_svn7768_3763"

><td id="3763"><a href="#3763">3763</a></td></tr
><tr id="gr_svn7768_3764"

><td id="3764"><a href="#3764">3764</a></td></tr
><tr id="gr_svn7768_3765"

><td id="3765"><a href="#3765">3765</a></td></tr
><tr id="gr_svn7768_3766"

><td id="3766"><a href="#3766">3766</a></td></tr
><tr id="gr_svn7768_3767"

><td id="3767"><a href="#3767">3767</a></td></tr
><tr id="gr_svn7768_3768"

><td id="3768"><a href="#3768">3768</a></td></tr
><tr id="gr_svn7768_3769"

><td id="3769"><a href="#3769">3769</a></td></tr
><tr id="gr_svn7768_3770"

><td id="3770"><a href="#3770">3770</a></td></tr
><tr id="gr_svn7768_3771"

><td id="3771"><a href="#3771">3771</a></td></tr
><tr id="gr_svn7768_3772"

><td id="3772"><a href="#3772">3772</a></td></tr
><tr id="gr_svn7768_3773"

><td id="3773"><a href="#3773">3773</a></td></tr
><tr id="gr_svn7768_3774"

><td id="3774"><a href="#3774">3774</a></td></tr
><tr id="gr_svn7768_3775"

><td id="3775"><a href="#3775">3775</a></td></tr
><tr id="gr_svn7768_3776"

><td id="3776"><a href="#3776">3776</a></td></tr
><tr id="gr_svn7768_3777"

><td id="3777"><a href="#3777">3777</a></td></tr
><tr id="gr_svn7768_3778"

><td id="3778"><a href="#3778">3778</a></td></tr
><tr id="gr_svn7768_3779"

><td id="3779"><a href="#3779">3779</a></td></tr
><tr id="gr_svn7768_3780"

><td id="3780"><a href="#3780">3780</a></td></tr
><tr id="gr_svn7768_3781"

><td id="3781"><a href="#3781">3781</a></td></tr
><tr id="gr_svn7768_3782"

><td id="3782"><a href="#3782">3782</a></td></tr
><tr id="gr_svn7768_3783"

><td id="3783"><a href="#3783">3783</a></td></tr
><tr id="gr_svn7768_3784"

><td id="3784"><a href="#3784">3784</a></td></tr
><tr id="gr_svn7768_3785"

><td id="3785"><a href="#3785">3785</a></td></tr
><tr id="gr_svn7768_3786"

><td id="3786"><a href="#3786">3786</a></td></tr
><tr id="gr_svn7768_3787"

><td id="3787"><a href="#3787">3787</a></td></tr
><tr id="gr_svn7768_3788"

><td id="3788"><a href="#3788">3788</a></td></tr
><tr id="gr_svn7768_3789"

><td id="3789"><a href="#3789">3789</a></td></tr
><tr id="gr_svn7768_3790"

><td id="3790"><a href="#3790">3790</a></td></tr
><tr id="gr_svn7768_3791"

><td id="3791"><a href="#3791">3791</a></td></tr
><tr id="gr_svn7768_3792"

><td id="3792"><a href="#3792">3792</a></td></tr
><tr id="gr_svn7768_3793"

><td id="3793"><a href="#3793">3793</a></td></tr
><tr id="gr_svn7768_3794"

><td id="3794"><a href="#3794">3794</a></td></tr
><tr id="gr_svn7768_3795"

><td id="3795"><a href="#3795">3795</a></td></tr
><tr id="gr_svn7768_3796"

><td id="3796"><a href="#3796">3796</a></td></tr
><tr id="gr_svn7768_3797"

><td id="3797"><a href="#3797">3797</a></td></tr
><tr id="gr_svn7768_3798"

><td id="3798"><a href="#3798">3798</a></td></tr
><tr id="gr_svn7768_3799"

><td id="3799"><a href="#3799">3799</a></td></tr
><tr id="gr_svn7768_3800"

><td id="3800"><a href="#3800">3800</a></td></tr
><tr id="gr_svn7768_3801"

><td id="3801"><a href="#3801">3801</a></td></tr
><tr id="gr_svn7768_3802"

><td id="3802"><a href="#3802">3802</a></td></tr
><tr id="gr_svn7768_3803"

><td id="3803"><a href="#3803">3803</a></td></tr
><tr id="gr_svn7768_3804"

><td id="3804"><a href="#3804">3804</a></td></tr
><tr id="gr_svn7768_3805"

><td id="3805"><a href="#3805">3805</a></td></tr
><tr id="gr_svn7768_3806"

><td id="3806"><a href="#3806">3806</a></td></tr
><tr id="gr_svn7768_3807"

><td id="3807"><a href="#3807">3807</a></td></tr
><tr id="gr_svn7768_3808"

><td id="3808"><a href="#3808">3808</a></td></tr
><tr id="gr_svn7768_3809"

><td id="3809"><a href="#3809">3809</a></td></tr
><tr id="gr_svn7768_3810"

><td id="3810"><a href="#3810">3810</a></td></tr
><tr id="gr_svn7768_3811"

><td id="3811"><a href="#3811">3811</a></td></tr
><tr id="gr_svn7768_3812"

><td id="3812"><a href="#3812">3812</a></td></tr
><tr id="gr_svn7768_3813"

><td id="3813"><a href="#3813">3813</a></td></tr
><tr id="gr_svn7768_3814"

><td id="3814"><a href="#3814">3814</a></td></tr
><tr id="gr_svn7768_3815"

><td id="3815"><a href="#3815">3815</a></td></tr
><tr id="gr_svn7768_3816"

><td id="3816"><a href="#3816">3816</a></td></tr
><tr id="gr_svn7768_3817"

><td id="3817"><a href="#3817">3817</a></td></tr
><tr id="gr_svn7768_3818"

><td id="3818"><a href="#3818">3818</a></td></tr
><tr id="gr_svn7768_3819"

><td id="3819"><a href="#3819">3819</a></td></tr
><tr id="gr_svn7768_3820"

><td id="3820"><a href="#3820">3820</a></td></tr
><tr id="gr_svn7768_3821"

><td id="3821"><a href="#3821">3821</a></td></tr
><tr id="gr_svn7768_3822"

><td id="3822"><a href="#3822">3822</a></td></tr
><tr id="gr_svn7768_3823"

><td id="3823"><a href="#3823">3823</a></td></tr
><tr id="gr_svn7768_3824"

><td id="3824"><a href="#3824">3824</a></td></tr
><tr id="gr_svn7768_3825"

><td id="3825"><a href="#3825">3825</a></td></tr
><tr id="gr_svn7768_3826"

><td id="3826"><a href="#3826">3826</a></td></tr
><tr id="gr_svn7768_3827"

><td id="3827"><a href="#3827">3827</a></td></tr
><tr id="gr_svn7768_3828"

><td id="3828"><a href="#3828">3828</a></td></tr
><tr id="gr_svn7768_3829"

><td id="3829"><a href="#3829">3829</a></td></tr
><tr id="gr_svn7768_3830"

><td id="3830"><a href="#3830">3830</a></td></tr
><tr id="gr_svn7768_3831"

><td id="3831"><a href="#3831">3831</a></td></tr
><tr id="gr_svn7768_3832"

><td id="3832"><a href="#3832">3832</a></td></tr
><tr id="gr_svn7768_3833"

><td id="3833"><a href="#3833">3833</a></td></tr
><tr id="gr_svn7768_3834"

><td id="3834"><a href="#3834">3834</a></td></tr
><tr id="gr_svn7768_3835"

><td id="3835"><a href="#3835">3835</a></td></tr
><tr id="gr_svn7768_3836"

><td id="3836"><a href="#3836">3836</a></td></tr
><tr id="gr_svn7768_3837"

><td id="3837"><a href="#3837">3837</a></td></tr
><tr id="gr_svn7768_3838"

><td id="3838"><a href="#3838">3838</a></td></tr
><tr id="gr_svn7768_3839"

><td id="3839"><a href="#3839">3839</a></td></tr
><tr id="gr_svn7768_3840"

><td id="3840"><a href="#3840">3840</a></td></tr
><tr id="gr_svn7768_3841"

><td id="3841"><a href="#3841">3841</a></td></tr
><tr id="gr_svn7768_3842"

><td id="3842"><a href="#3842">3842</a></td></tr
><tr id="gr_svn7768_3843"

><td id="3843"><a href="#3843">3843</a></td></tr
><tr id="gr_svn7768_3844"

><td id="3844"><a href="#3844">3844</a></td></tr
><tr id="gr_svn7768_3845"

><td id="3845"><a href="#3845">3845</a></td></tr
><tr id="gr_svn7768_3846"

><td id="3846"><a href="#3846">3846</a></td></tr
><tr id="gr_svn7768_3847"

><td id="3847"><a href="#3847">3847</a></td></tr
><tr id="gr_svn7768_3848"

><td id="3848"><a href="#3848">3848</a></td></tr
><tr id="gr_svn7768_3849"

><td id="3849"><a href="#3849">3849</a></td></tr
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

><td class="source">  Copyright (c) 2004-07 Ben Fry and Casey Reas<br></td></tr
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

><td class="source"> */<br></td></tr
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

><td class="source">/**<br></td></tr
><tr
id=sl_svn7768_28

><td class="source"> * Handles rendering of single (tesselated) triangles in 3D.<br></td></tr
><tr
id=sl_svn7768_29

><td class="source"> * &lt;P&gt;<br></td></tr
><tr
id=sl_svn7768_30

><td class="source"> * Originally written by sami (www.sumea.com)<br></td></tr
><tr
id=sl_svn7768_31

><td class="source"> */<br></td></tr
><tr
id=sl_svn7768_32

><td class="source">public class PTriangle implements PConstants<br></td></tr
><tr
id=sl_svn7768_33

><td class="source">{<br></td></tr
><tr
id=sl_svn7768_34

><td class="source">  static final float PIXEL_CENTER = 0.5f;  // for polygon aa<br></td></tr
><tr
id=sl_svn7768_35

><td class="source"><br></td></tr
><tr
id=sl_svn7768_36

><td class="source">  static final int R_GOURAUD = 0x1;<br></td></tr
><tr
id=sl_svn7768_37

><td class="source">  static final int R_TEXTURE8 = 0x2;<br></td></tr
><tr
id=sl_svn7768_38

><td class="source">  static final int R_TEXTURE24 = 0x4;<br></td></tr
><tr
id=sl_svn7768_39

><td class="source">  static final int R_TEXTURE32 = 0x8;<br></td></tr
><tr
id=sl_svn7768_40

><td class="source">  static final int R_ALPHA = 0x10;<br></td></tr
><tr
id=sl_svn7768_41

><td class="source"><br></td></tr
><tr
id=sl_svn7768_42

><td class="source">  private int[] m_pixels;<br></td></tr
><tr
id=sl_svn7768_43

><td class="source">  private int[] m_texture;<br></td></tr
><tr
id=sl_svn7768_44

><td class="source">  //private int[] m_stencil;<br></td></tr
><tr
id=sl_svn7768_45

><td class="source">  private float[] m_zbuffer;<br></td></tr
><tr
id=sl_svn7768_46

><td class="source"><br></td></tr
><tr
id=sl_svn7768_47

><td class="source">  private int SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_48

><td class="source">  private int SCREEN_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_49

><td class="source">  //private int SCREEN_WIDTH1;<br></td></tr
><tr
id=sl_svn7768_50

><td class="source">  //private int SCREEN_HEIGHT1;<br></td></tr
><tr
id=sl_svn7768_51

><td class="source"><br></td></tr
><tr
id=sl_svn7768_52

><td class="source">  private int TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_53

><td class="source">  private int TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_54

><td class="source">  private float F_TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_55

><td class="source">  private float F_TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_56

><td class="source"><br></td></tr
><tr
id=sl_svn7768_57

><td class="source">  public boolean INTERPOLATE_UV;<br></td></tr
><tr
id=sl_svn7768_58

><td class="source">  public boolean INTERPOLATE_RGB;<br></td></tr
><tr
id=sl_svn7768_59

><td class="source">  public boolean INTERPOLATE_ALPHA;<br></td></tr
><tr
id=sl_svn7768_60

><td class="source"><br></td></tr
><tr
id=sl_svn7768_61

><td class="source">  // the power of 2 that tells how many pixels to interpolate<br></td></tr
><tr
id=sl_svn7768_62

><td class="source">  // for between  exactly computed texture coordinates<br></td></tr
><tr
id=sl_svn7768_63

><td class="source">  private static final int DEFAULT_INTERP_POWER = 3;<br></td></tr
><tr
id=sl_svn7768_64

><td class="source">  private static int TEX_INTERP_POWER = DEFAULT_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_65

><td class="source"><br></td></tr
><tr
id=sl_svn7768_66

><td class="source">  // Vertex coordinates<br></td></tr
><tr
id=sl_svn7768_67

><td class="source">  private float[] x_array;<br></td></tr
><tr
id=sl_svn7768_68

><td class="source">  private float[] y_array;<br></td></tr
><tr
id=sl_svn7768_69

><td class="source">  private float[] z_array;<br></td></tr
><tr
id=sl_svn7768_70

><td class="source"><br></td></tr
><tr
id=sl_svn7768_71

><td class="source">  private float[] camX;<br></td></tr
><tr
id=sl_svn7768_72

><td class="source">  private float[] camY;<br></td></tr
><tr
id=sl_svn7768_73

><td class="source">  private float[] camZ;<br></td></tr
><tr
id=sl_svn7768_74

><td class="source"><br></td></tr
><tr
id=sl_svn7768_75

><td class="source">  // U,V coordinates<br></td></tr
><tr
id=sl_svn7768_76

><td class="source">  private float[] u_array;<br></td></tr
><tr
id=sl_svn7768_77

><td class="source">  private float[] v_array;<br></td></tr
><tr
id=sl_svn7768_78

><td class="source"><br></td></tr
><tr
id=sl_svn7768_79

><td class="source">  // Vertex Intensity<br></td></tr
><tr
id=sl_svn7768_80

><td class="source">  private float[] r_array;<br></td></tr
><tr
id=sl_svn7768_81

><td class="source">  private float[] g_array;<br></td></tr
><tr
id=sl_svn7768_82

><td class="source">  private float[] b_array;<br></td></tr
><tr
id=sl_svn7768_83

><td class="source">  private float[] a_array;<br></td></tr
><tr
id=sl_svn7768_84

><td class="source"><br></td></tr
><tr
id=sl_svn7768_85

><td class="source">  // vertex offsets<br></td></tr
><tr
id=sl_svn7768_86

><td class="source">  private int o0;<br></td></tr
><tr
id=sl_svn7768_87

><td class="source">  private int o1;<br></td></tr
><tr
id=sl_svn7768_88

><td class="source">  private int o2;<br></td></tr
><tr
id=sl_svn7768_89

><td class="source"><br></td></tr
><tr
id=sl_svn7768_90

><td class="source">  /* rgb &amp; a */<br></td></tr
><tr
id=sl_svn7768_91

><td class="source">  private float r0;<br></td></tr
><tr
id=sl_svn7768_92

><td class="source">  private float r1;<br></td></tr
><tr
id=sl_svn7768_93

><td class="source">  private float r2;<br></td></tr
><tr
id=sl_svn7768_94

><td class="source">  private float g0;<br></td></tr
><tr
id=sl_svn7768_95

><td class="source">  private float g1;<br></td></tr
><tr
id=sl_svn7768_96

><td class="source">  private float g2;<br></td></tr
><tr
id=sl_svn7768_97

><td class="source">  private float b0;<br></td></tr
><tr
id=sl_svn7768_98

><td class="source">  private float b1;<br></td></tr
><tr
id=sl_svn7768_99

><td class="source">  private float b2;<br></td></tr
><tr
id=sl_svn7768_100

><td class="source">  private float a0;<br></td></tr
><tr
id=sl_svn7768_101

><td class="source">  private float a1;<br></td></tr
><tr
id=sl_svn7768_102

><td class="source">  private float a2;<br></td></tr
><tr
id=sl_svn7768_103

><td class="source"><br></td></tr
><tr
id=sl_svn7768_104

><td class="source">  /* accurate texture uv coordinates */<br></td></tr
><tr
id=sl_svn7768_105

><td class="source">  private float u0;<br></td></tr
><tr
id=sl_svn7768_106

><td class="source">  private float u1;<br></td></tr
><tr
id=sl_svn7768_107

><td class="source">  private float u2;<br></td></tr
><tr
id=sl_svn7768_108

><td class="source">  private float v0;<br></td></tr
><tr
id=sl_svn7768_109

><td class="source">  private float v1;<br></td></tr
><tr
id=sl_svn7768_110

><td class="source">  private float v2;<br></td></tr
><tr
id=sl_svn7768_111

><td class="source"><br></td></tr
><tr
id=sl_svn7768_112

><td class="source">  /* deltas */<br></td></tr
><tr
id=sl_svn7768_113

><td class="source">  //private float dx0;<br></td></tr
><tr
id=sl_svn7768_114

><td class="source">  //private float dx1;<br></td></tr
><tr
id=sl_svn7768_115

><td class="source">  private float dx2;<br></td></tr
><tr
id=sl_svn7768_116

><td class="source">  private float dy0;<br></td></tr
><tr
id=sl_svn7768_117

><td class="source">  private float dy1;<br></td></tr
><tr
id=sl_svn7768_118

><td class="source">  private float dy2;<br></td></tr
><tr
id=sl_svn7768_119

><td class="source">  private float dz0;<br></td></tr
><tr
id=sl_svn7768_120

><td class="source">  //private float dz1;<br></td></tr
><tr
id=sl_svn7768_121

><td class="source">  private float dz2;<br></td></tr
><tr
id=sl_svn7768_122

><td class="source"><br></td></tr
><tr
id=sl_svn7768_123

><td class="source">  /* texture deltas */<br></td></tr
><tr
id=sl_svn7768_124

><td class="source">  private float du0;<br></td></tr
><tr
id=sl_svn7768_125

><td class="source">  //private float du1;<br></td></tr
><tr
id=sl_svn7768_126

><td class="source">  private float du2;<br></td></tr
><tr
id=sl_svn7768_127

><td class="source">  private float dv0;<br></td></tr
><tr
id=sl_svn7768_128

><td class="source">  //private float dv1;<br></td></tr
><tr
id=sl_svn7768_129

><td class="source">  private float dv2;<br></td></tr
><tr
id=sl_svn7768_130

><td class="source"><br></td></tr
><tr
id=sl_svn7768_131

><td class="source">  /* rgba deltas */<br></td></tr
><tr
id=sl_svn7768_132

><td class="source">  private float dr0;<br></td></tr
><tr
id=sl_svn7768_133

><td class="source">  //private float dr1;<br></td></tr
><tr
id=sl_svn7768_134

><td class="source">  private float dr2;<br></td></tr
><tr
id=sl_svn7768_135

><td class="source">  private float dg0;<br></td></tr
><tr
id=sl_svn7768_136

><td class="source">  //private float dg1;<br></td></tr
><tr
id=sl_svn7768_137

><td class="source">  private float dg2;<br></td></tr
><tr
id=sl_svn7768_138

><td class="source">  private float db0;<br></td></tr
><tr
id=sl_svn7768_139

><td class="source">  //private float db1;<br></td></tr
><tr
id=sl_svn7768_140

><td class="source">  private float db2;<br></td></tr
><tr
id=sl_svn7768_141

><td class="source">  private float da0;<br></td></tr
><tr
id=sl_svn7768_142

><td class="source">  //private float da1;<br></td></tr
><tr
id=sl_svn7768_143

><td class="source">  private float da2;<br></td></tr
><tr
id=sl_svn7768_144

><td class="source"><br></td></tr
><tr
id=sl_svn7768_145

><td class="source">  /* */<br></td></tr
><tr
id=sl_svn7768_146

><td class="source">  private float uleft;<br></td></tr
><tr
id=sl_svn7768_147

><td class="source">  private float vleft;<br></td></tr
><tr
id=sl_svn7768_148

><td class="source">  private float uleftadd;<br></td></tr
><tr
id=sl_svn7768_149

><td class="source">  private float vleftadd;<br></td></tr
><tr
id=sl_svn7768_150

><td class="source"><br></td></tr
><tr
id=sl_svn7768_151

><td class="source">  /* polyedge positions &amp; adds */<br></td></tr
><tr
id=sl_svn7768_152

><td class="source">  private float xleft;<br></td></tr
><tr
id=sl_svn7768_153

><td class="source">  private float xrght;<br></td></tr
><tr
id=sl_svn7768_154

><td class="source">  private float xadd1;<br></td></tr
><tr
id=sl_svn7768_155

><td class="source">  private float xadd2;<br></td></tr
><tr
id=sl_svn7768_156

><td class="source">  private float zleft;<br></td></tr
><tr
id=sl_svn7768_157

><td class="source">  private float zleftadd;<br></td></tr
><tr
id=sl_svn7768_158

><td class="source"><br></td></tr
><tr
id=sl_svn7768_159

><td class="source">  /* rgba positions &amp; adds */<br></td></tr
><tr
id=sl_svn7768_160

><td class="source">  private float rleft;<br></td></tr
><tr
id=sl_svn7768_161

><td class="source">  private float gleft;<br></td></tr
><tr
id=sl_svn7768_162

><td class="source">  private float bleft;<br></td></tr
><tr
id=sl_svn7768_163

><td class="source">  private float aleft;<br></td></tr
><tr
id=sl_svn7768_164

><td class="source">  private float rleftadd;<br></td></tr
><tr
id=sl_svn7768_165

><td class="source">  private float gleftadd;<br></td></tr
><tr
id=sl_svn7768_166

><td class="source">  private float bleftadd;<br></td></tr
><tr
id=sl_svn7768_167

><td class="source">  private float aleftadd;<br></td></tr
><tr
id=sl_svn7768_168

><td class="source"><br></td></tr
><tr
id=sl_svn7768_169

><td class="source">  /* other somewhat useful variables :) */<br></td></tr
><tr
id=sl_svn7768_170

><td class="source">  private float dta;<br></td></tr
><tr
id=sl_svn7768_171

><td class="source">  //private float dta2;<br></td></tr
><tr
id=sl_svn7768_172

><td class="source">  private float temp;<br></td></tr
><tr
id=sl_svn7768_173

><td class="source">  private float width;<br></td></tr
><tr
id=sl_svn7768_174

><td class="source"><br></td></tr
><tr
id=sl_svn7768_175

><td class="source">  /* integer poly UV adds */<br></td></tr
><tr
id=sl_svn7768_176

><td class="source">  private int iuadd;<br></td></tr
><tr
id=sl_svn7768_177

><td class="source">  private int ivadd;<br></td></tr
><tr
id=sl_svn7768_178

><td class="source">  private int iradd;<br></td></tr
><tr
id=sl_svn7768_179

><td class="source">  private int igadd;<br></td></tr
><tr
id=sl_svn7768_180

><td class="source">  private int ibadd;<br></td></tr
><tr
id=sl_svn7768_181

><td class="source">  private int iaadd;<br></td></tr
><tr
id=sl_svn7768_182

><td class="source">  private float izadd;<br></td></tr
><tr
id=sl_svn7768_183

><td class="source"><br></td></tr
><tr
id=sl_svn7768_184

><td class="source">  /* fill color */<br></td></tr
><tr
id=sl_svn7768_185

><td class="source">  private int m_fill;<br></td></tr
><tr
id=sl_svn7768_186

><td class="source"><br></td></tr
><tr
id=sl_svn7768_187

><td class="source">  /* draw flags */<br></td></tr
><tr
id=sl_svn7768_188

><td class="source">  public int  m_drawFlags;<br></td></tr
><tr
id=sl_svn7768_189

><td class="source"><br></td></tr
><tr
id=sl_svn7768_190

><td class="source">  /* current poly number */<br></td></tr
><tr
id=sl_svn7768_191

><td class="source">//  private int m_index;<br></td></tr
><tr
id=sl_svn7768_192

><td class="source"><br></td></tr
><tr
id=sl_svn7768_193

><td class="source">  /** */<br></td></tr
><tr
id=sl_svn7768_194

><td class="source">  private PGraphics3D parent;<br></td></tr
><tr
id=sl_svn7768_195

><td class="source"><br></td></tr
><tr
id=sl_svn7768_196

><td class="source">  private boolean noDepthTest;<br></td></tr
><tr
id=sl_svn7768_197

><td class="source">  //private boolean argbSurface;<br></td></tr
><tr
id=sl_svn7768_198

><td class="source"><br></td></tr
><tr
id=sl_svn7768_199

><td class="source">  /** */<br></td></tr
><tr
id=sl_svn7768_200

><td class="source">  private boolean m_culling;<br></td></tr
><tr
id=sl_svn7768_201

><td class="source"><br></td></tr
><tr
id=sl_svn7768_202

><td class="source">  /** */<br></td></tr
><tr
id=sl_svn7768_203

><td class="source">  private boolean m_singleRight;<br></td></tr
><tr
id=sl_svn7768_204

><td class="source"><br></td></tr
><tr
id=sl_svn7768_205

><td class="source">  /** <br></td></tr
><tr
id=sl_svn7768_206

><td class="source">   * True if using bilinear interpolation for textures.<br></td></tr
><tr
id=sl_svn7768_207

><td class="source">   * Always set to true. If this is ever changed (maybe with a hint()?)<br></td></tr
><tr
id=sl_svn7768_208

><td class="source">   * will need to write code for texture8/24/32 et al that will handle mixing<br></td></tr
><tr
id=sl_svn7768_209

><td class="source">   * the m_fill color in with the texture color.  <br></td></tr
><tr
id=sl_svn7768_210

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_211

><td class="source">  private boolean m_bilinear = true;  // always set to true<br></td></tr
><tr
id=sl_svn7768_212

><td class="source"><br></td></tr
><tr
id=sl_svn7768_213

><td class="source"><br></td></tr
><tr
id=sl_svn7768_214

><td class="source">  // Vectors needed in accurate texture code<br></td></tr
><tr
id=sl_svn7768_215

><td class="source">  // We store them as class members to avoid too much code duplication<br></td></tr
><tr
id=sl_svn7768_216

><td class="source">  private float ax,ay,az;<br></td></tr
><tr
id=sl_svn7768_217

><td class="source">  private float bx,by,bz;<br></td></tr
><tr
id=sl_svn7768_218

><td class="source">  private float cx,cy,cz;<br></td></tr
><tr
id=sl_svn7768_219

><td class="source">  private float nearPlaneWidth;<br></td></tr
><tr
id=sl_svn7768_220

><td class="source">  private float nearPlaneHeight;<br></td></tr
><tr
id=sl_svn7768_221

><td class="source">  private float nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_222

><td class="source">  private float xmult;<br></td></tr
><tr
id=sl_svn7768_223

><td class="source">  private float ymult;<br></td></tr
><tr
id=sl_svn7768_224

><td class="source">  // optimization vars...not pretty, but save a couple mults per pixel<br></td></tr
><tr
id=sl_svn7768_225

><td class="source">  private float newax,newbx,newcx;<br></td></tr
><tr
id=sl_svn7768_226

><td class="source">  // are we currently drawing the first piece of the triangle,<br></td></tr
><tr
id=sl_svn7768_227

><td class="source">  // or have we already done so?<br></td></tr
><tr
id=sl_svn7768_228

><td class="source">  private boolean firstSegment;<br></td></tr
><tr
id=sl_svn7768_229

><td class="source"><br></td></tr
><tr
id=sl_svn7768_230

><td class="source"><br></td></tr
><tr
id=sl_svn7768_231

><td class="source">  public PTriangle(PGraphics3D g) {<br></td></tr
><tr
id=sl_svn7768_232

><td class="source">    x_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_233

><td class="source">    y_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_234

><td class="source">    z_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_235

><td class="source">    u_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_236

><td class="source">    v_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_237

><td class="source">    r_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_238

><td class="source">    g_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_239

><td class="source">    b_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_240

><td class="source">    a_array = new float[3];<br></td></tr
><tr
id=sl_svn7768_241

><td class="source"><br></td></tr
><tr
id=sl_svn7768_242

><td class="source">    camX = new float[3];<br></td></tr
><tr
id=sl_svn7768_243

><td class="source">    camY = new float[3];<br></td></tr
><tr
id=sl_svn7768_244

><td class="source">    camZ = new float[3];<br></td></tr
><tr
id=sl_svn7768_245

><td class="source"><br></td></tr
><tr
id=sl_svn7768_246

><td class="source">    this.parent = g;<br></td></tr
><tr
id=sl_svn7768_247

><td class="source">    reset();<br></td></tr
><tr
id=sl_svn7768_248

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_249

><td class="source"><br></td></tr
><tr
id=sl_svn7768_250

><td class="source"><br></td></tr
><tr
id=sl_svn7768_251

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_252

><td class="source">   * Resets polygon attributes<br></td></tr
><tr
id=sl_svn7768_253

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_254

><td class="source">  public void reset() {<br></td></tr
><tr
id=sl_svn7768_255

><td class="source">    // reset these in case PGraphics was resized<br></td></tr
><tr
id=sl_svn7768_256

><td class="source"><br></td></tr
><tr
id=sl_svn7768_257

><td class="source">    SCREEN_WIDTH = parent.width;<br></td></tr
><tr
id=sl_svn7768_258

><td class="source">    SCREEN_HEIGHT = parent.height;<br></td></tr
><tr
id=sl_svn7768_259

><td class="source">    //SCREEN_WIDTH1 = SCREEN_WIDTH-1;<br></td></tr
><tr
id=sl_svn7768_260

><td class="source">    //SCREEN_HEIGHT1 = SCREEN_HEIGHT-1;<br></td></tr
><tr
id=sl_svn7768_261

><td class="source"><br></td></tr
><tr
id=sl_svn7768_262

><td class="source">    m_pixels = parent.pixels;<br></td></tr
><tr
id=sl_svn7768_263

><td class="source">//    m_stencil = parent.stencil;<br></td></tr
><tr
id=sl_svn7768_264

><td class="source">    m_zbuffer = parent.zbuffer;<br></td></tr
><tr
id=sl_svn7768_265

><td class="source"><br></td></tr
><tr
id=sl_svn7768_266

><td class="source">    noDepthTest = parent.hints[DISABLE_DEPTH_TEST];<br></td></tr
><tr
id=sl_svn7768_267

><td class="source">    //argbSurface = parent.format == PConstants.ARGB;<br></td></tr
><tr
id=sl_svn7768_268

><td class="source"><br></td></tr
><tr
id=sl_svn7768_269

><td class="source">    // other things to reset<br></td></tr
><tr
id=sl_svn7768_270

><td class="source"><br></td></tr
><tr
id=sl_svn7768_271

><td class="source">    INTERPOLATE_UV = false;<br></td></tr
><tr
id=sl_svn7768_272

><td class="source">    INTERPOLATE_RGB = false;<br></td></tr
><tr
id=sl_svn7768_273

><td class="source">    INTERPOLATE_ALPHA = false;<br></td></tr
><tr
id=sl_svn7768_274

><td class="source">    //m_tImage = null;<br></td></tr
><tr
id=sl_svn7768_275

><td class="source">    m_texture = null;<br></td></tr
><tr
id=sl_svn7768_276

><td class="source">    m_drawFlags = 0;<br></td></tr
><tr
id=sl_svn7768_277

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_278

><td class="source"><br></td></tr
><tr
id=sl_svn7768_279

><td class="source"><br></td></tr
><tr
id=sl_svn7768_280

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_281

><td class="source">   * Sets backface culling on/off<br></td></tr
><tr
id=sl_svn7768_282

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_283

><td class="source">  public void setCulling(boolean tf) {<br></td></tr
><tr
id=sl_svn7768_284

><td class="source">    m_culling = tf;<br></td></tr
><tr
id=sl_svn7768_285

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_286

><td class="source"><br></td></tr
><tr
id=sl_svn7768_287

><td class="source"><br></td></tr
><tr
id=sl_svn7768_288

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_289

><td class="source">   * Sets vertex coordinates for the triangle<br></td></tr
><tr
id=sl_svn7768_290

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_291

><td class="source">  public void setVertices(float x0, float y0, float z0,<br></td></tr
><tr
id=sl_svn7768_292

><td class="source">                          float x1, float y1, float z1,<br></td></tr
><tr
id=sl_svn7768_293

><td class="source">                          float x2, float y2, float z2) {<br></td></tr
><tr
id=sl_svn7768_294

><td class="source">    x_array[0] = x0;<br></td></tr
><tr
id=sl_svn7768_295

><td class="source">    x_array[1] = x1;<br></td></tr
><tr
id=sl_svn7768_296

><td class="source">    x_array[2] = x2;<br></td></tr
><tr
id=sl_svn7768_297

><td class="source"><br></td></tr
><tr
id=sl_svn7768_298

><td class="source">    y_array[0] = y0;<br></td></tr
><tr
id=sl_svn7768_299

><td class="source">    y_array[1] = y1;<br></td></tr
><tr
id=sl_svn7768_300

><td class="source">    y_array[2] = y2;<br></td></tr
><tr
id=sl_svn7768_301

><td class="source"><br></td></tr
><tr
id=sl_svn7768_302

><td class="source">    z_array[0] = z0;<br></td></tr
><tr
id=sl_svn7768_303

><td class="source">    z_array[1] = z1;<br></td></tr
><tr
id=sl_svn7768_304

><td class="source">    z_array[2] = z2;<br></td></tr
><tr
id=sl_svn7768_305

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_306

><td class="source"><br></td></tr
><tr
id=sl_svn7768_307

><td class="source"><br></td></tr
><tr
id=sl_svn7768_308

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_309

><td class="source">   * Pass camera-space coordinates for the triangle.<br></td></tr
><tr
id=sl_svn7768_310

><td class="source">   * Needed to render if hint(ENABLE_ACCURATE_TEXTURES) enabled.<br></td></tr
><tr
id=sl_svn7768_311

><td class="source">   * Generally this will not need to be called manually,<br></td></tr
><tr
id=sl_svn7768_312

><td class="source">   * currently called from PGraphics3D.render_triangles()<br></td></tr
><tr
id=sl_svn7768_313

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_314

><td class="source">  public void setCamVertices(float x0, float y0, float z0,<br></td></tr
><tr
id=sl_svn7768_315

><td class="source">                          float x1, float y1, float z1,<br></td></tr
><tr
id=sl_svn7768_316

><td class="source">                          float x2, float y2, float z2) {<br></td></tr
><tr
id=sl_svn7768_317

><td class="source">    camX[0] = x0;<br></td></tr
><tr
id=sl_svn7768_318

><td class="source">    camX[1] = x1;<br></td></tr
><tr
id=sl_svn7768_319

><td class="source">    camX[2] = x2;<br></td></tr
><tr
id=sl_svn7768_320

><td class="source"><br></td></tr
><tr
id=sl_svn7768_321

><td class="source">    camY[0] = y0;<br></td></tr
><tr
id=sl_svn7768_322

><td class="source">    camY[1] = y1;<br></td></tr
><tr
id=sl_svn7768_323

><td class="source">    camY[2] = y2;<br></td></tr
><tr
id=sl_svn7768_324

><td class="source"><br></td></tr
><tr
id=sl_svn7768_325

><td class="source">    camZ[0] = z0;<br></td></tr
><tr
id=sl_svn7768_326

><td class="source">    camZ[1] = z1;<br></td></tr
><tr
id=sl_svn7768_327

><td class="source">    camZ[2] = z2;<br></td></tr
><tr
id=sl_svn7768_328

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_329

><td class="source"><br></td></tr
><tr
id=sl_svn7768_330

><td class="source"><br></td></tr
><tr
id=sl_svn7768_331

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_332

><td class="source">   * Sets the UV coordinates of the texture<br></td></tr
><tr
id=sl_svn7768_333

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_334

><td class="source">  public void setUV(float u0, float v0,<br></td></tr
><tr
id=sl_svn7768_335

><td class="source">                    float u1, float v1,<br></td></tr
><tr
id=sl_svn7768_336

><td class="source">                    float u2, float v2) {<br></td></tr
><tr
id=sl_svn7768_337

><td class="source">    // sets &amp; scales uv texture coordinates to center of the pixel<br></td></tr
><tr
id=sl_svn7768_338

><td class="source">    u_array[0] = (u0 * F_TEX_WIDTH + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_339

><td class="source">    u_array[1] = (u1 * F_TEX_WIDTH + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_340

><td class="source">    u_array[2] = (u2 * F_TEX_WIDTH + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_341

><td class="source">    v_array[0] = (v0 * F_TEX_HEIGHT + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_342

><td class="source">    v_array[1] = (v1 * F_TEX_HEIGHT + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_343

><td class="source">    v_array[2] = (v2 * F_TEX_HEIGHT + 0.5f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_344

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_345

><td class="source"><br></td></tr
><tr
id=sl_svn7768_346

><td class="source"><br></td></tr
><tr
id=sl_svn7768_347

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_348

><td class="source">   * Sets vertex intensities in 0xRRGGBBAA format<br></td></tr
><tr
id=sl_svn7768_349

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_350

><td class="source">  public void setIntensities(float r0, float g0, float b0, float a0,<br></td></tr
><tr
id=sl_svn7768_351

><td class="source">                             float r1, float g1, float b1, float a1,<br></td></tr
><tr
id=sl_svn7768_352

><td class="source">                             float r2, float g2, float b2, float a2) {<br></td></tr
><tr
id=sl_svn7768_353

><td class="source">    // Check if we need alpha or not?<br></td></tr
><tr
id=sl_svn7768_354

><td class="source">    if ((a0 != 1.0f) || (a1 != 1.0f) || (a2 != 1.0f)) {<br></td></tr
><tr
id=sl_svn7768_355

><td class="source">      INTERPOLATE_ALPHA = true;<br></td></tr
><tr
id=sl_svn7768_356

><td class="source">      a_array[0] = (a0 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_357

><td class="source">      a_array[1] = (a1 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_358

><td class="source">      a_array[2] = (a2 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_359

><td class="source">      m_drawFlags|=R_ALPHA;<br></td></tr
><tr
id=sl_svn7768_360

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_361

><td class="source">      INTERPOLATE_ALPHA = false;<br></td></tr
><tr
id=sl_svn7768_362

><td class="source">      m_drawFlags&amp;=~R_ALPHA;<br></td></tr
><tr
id=sl_svn7768_363

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_364

><td class="source"><br></td></tr
><tr
id=sl_svn7768_365

><td class="source">    // Check if we need to interpolate the intensity values<br></td></tr
><tr
id=sl_svn7768_366

><td class="source">    if ((r0 != r1) || (r1 != r2)) {<br></td></tr
><tr
id=sl_svn7768_367

><td class="source">      INTERPOLATE_RGB = true;<br></td></tr
><tr
id=sl_svn7768_368

><td class="source">      m_drawFlags |= R_GOURAUD;<br></td></tr
><tr
id=sl_svn7768_369

><td class="source">    } else if ((g0 != g1) || (g1 != g2)) {<br></td></tr
><tr
id=sl_svn7768_370

><td class="source">      INTERPOLATE_RGB = true;<br></td></tr
><tr
id=sl_svn7768_371

><td class="source">      m_drawFlags |= R_GOURAUD;<br></td></tr
><tr
id=sl_svn7768_372

><td class="source">    } else if ((b0 != b1) || (b1 != b2)) {<br></td></tr
><tr
id=sl_svn7768_373

><td class="source">      INTERPOLATE_RGB = true;<br></td></tr
><tr
id=sl_svn7768_374

><td class="source">      m_drawFlags |= R_GOURAUD;<br></td></tr
><tr
id=sl_svn7768_375

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_376

><td class="source">      //m_fill = parent.filli;<br></td></tr
><tr
id=sl_svn7768_377

><td class="source">      m_drawFlags &amp;=~ R_GOURAUD;<br></td></tr
><tr
id=sl_svn7768_378

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_379

><td class="source"><br></td></tr
><tr
id=sl_svn7768_380

><td class="source">    // push values to arrays.. some extra scaling is added<br></td></tr
><tr
id=sl_svn7768_381

><td class="source">    // to prevent possible color &quot;overflood&quot; due to rounding errors<br></td></tr
><tr
id=sl_svn7768_382

><td class="source">    r_array[0] = (r0 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_383

><td class="source">    r_array[1] = (r1 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_384

><td class="source">    r_array[2] = (r2 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_385

><td class="source"><br></td></tr
><tr
id=sl_svn7768_386

><td class="source">    g_array[0] = (g0 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_387

><td class="source">    g_array[1] = (g1 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_388

><td class="source">    g_array[2] = (g2 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_389

><td class="source"><br></td></tr
><tr
id=sl_svn7768_390

><td class="source">    b_array[0] = (b0 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_391

><td class="source">    b_array[1] = (b1 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_392

><td class="source">    b_array[2] = (b2 * 253f + 1.0f) * 65536f;<br></td></tr
><tr
id=sl_svn7768_393

><td class="source"><br></td></tr
><tr
id=sl_svn7768_394

><td class="source">    // for plain triangles<br></td></tr
><tr
id=sl_svn7768_395

><td class="source">    m_fill = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_396

><td class="source">      ((int)(255*r0) &lt;&lt; 16) | ((int)(255*g0) &lt;&lt; 8) | (int)(255*b0);<br></td></tr
><tr
id=sl_svn7768_397

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_398

><td class="source"><br></td></tr
><tr
id=sl_svn7768_399

><td class="source"><br></td></tr
><tr
id=sl_svn7768_400

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_401

><td class="source">   * Sets texture image used for the polygon<br></td></tr
><tr
id=sl_svn7768_402

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_403

><td class="source">  public void setTexture(PImage image) {<br></td></tr
><tr
id=sl_svn7768_404

><td class="source">    //m_tImage = image;<br></td></tr
><tr
id=sl_svn7768_405

><td class="source">    m_texture = image.pixels;<br></td></tr
><tr
id=sl_svn7768_406

><td class="source">    TEX_WIDTH = image.width;<br></td></tr
><tr
id=sl_svn7768_407

><td class="source">    TEX_HEIGHT = image.height;<br></td></tr
><tr
id=sl_svn7768_408

><td class="source">    F_TEX_WIDTH = TEX_WIDTH-1;<br></td></tr
><tr
id=sl_svn7768_409

><td class="source">    F_TEX_HEIGHT = TEX_HEIGHT-1;<br></td></tr
><tr
id=sl_svn7768_410

><td class="source">    INTERPOLATE_UV = true;<br></td></tr
><tr
id=sl_svn7768_411

><td class="source"><br></td></tr
><tr
id=sl_svn7768_412

><td class="source">    if (image.format == ARGB) {<br></td></tr
><tr
id=sl_svn7768_413

><td class="source">      m_drawFlags |= R_TEXTURE32;<br></td></tr
><tr
id=sl_svn7768_414

><td class="source">    } else if (image.format == RGB) {<br></td></tr
><tr
id=sl_svn7768_415

><td class="source">      m_drawFlags |= R_TEXTURE24;<br></td></tr
><tr
id=sl_svn7768_416

><td class="source">    } else if (image.format == ALPHA) {<br></td></tr
><tr
id=sl_svn7768_417

><td class="source">      m_drawFlags |= R_TEXTURE8;<br></td></tr
><tr
id=sl_svn7768_418

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_419

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_420

><td class="source"><br></td></tr
><tr
id=sl_svn7768_421

><td class="source"><br></td></tr
><tr
id=sl_svn7768_422

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_423

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_424

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_425

><td class="source">  public void setUV(float[] u, float[] v) {<br></td></tr
><tr
id=sl_svn7768_426

><td class="source">    if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_427

><td class="source">      // sets &amp; scales uv texture coordinates to edges of pixels<br></td></tr
><tr
id=sl_svn7768_428

><td class="source">      u_array[0] = (u[0] * F_TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_429

><td class="source">      u_array[1] = (u[1] * F_TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_430

><td class="source">      u_array[2] = (u[2] * F_TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_431

><td class="source">      v_array[0] = (v[0] * F_TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_432

><td class="source">      v_array[1] = (v[1] * F_TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_433

><td class="source">      v_array[2] = (v[2] * F_TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_434

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_435

><td class="source">      // sets &amp; scales uv texture coordinates to center of the pixel<br></td></tr
><tr
id=sl_svn7768_436

><td class="source">      u_array[0] = (u[0] * TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_437

><td class="source">      u_array[1] = (u[1] * TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_438

><td class="source">      u_array[2] = (u[2] * TEX_WIDTH) * 65500f;<br></td></tr
><tr
id=sl_svn7768_439

><td class="source">      v_array[0] = (v[0] * TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_440

><td class="source">      v_array[1] = (v[1] * TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_441

><td class="source">      v_array[2] = (v[2] * TEX_HEIGHT) * 65500f;<br></td></tr
><tr
id=sl_svn7768_442

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_443

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_444

><td class="source"><br></td></tr
><tr
id=sl_svn7768_445

><td class="source"><br></td></tr
><tr
id=sl_svn7768_446

><td class="source">//  public void setIndex(int index) {<br></td></tr
><tr
id=sl_svn7768_447

><td class="source">//    m_index = index;<br></td></tr
><tr
id=sl_svn7768_448

><td class="source">//  }<br></td></tr
><tr
id=sl_svn7768_449

><td class="source"><br></td></tr
><tr
id=sl_svn7768_450

><td class="source"><br></td></tr
><tr
id=sl_svn7768_451

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_452

><td class="source">   * Renders the polygon<br></td></tr
><tr
id=sl_svn7768_453

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_454

><td class="source">  public void render() {<br></td></tr
><tr
id=sl_svn7768_455

><td class="source">    float x0, x1, x2;<br></td></tr
><tr
id=sl_svn7768_456

><td class="source">    float z0, z1, z2;<br></td></tr
><tr
id=sl_svn7768_457

><td class="source"><br></td></tr
><tr
id=sl_svn7768_458

><td class="source">    float y0 = y_array[0];<br></td></tr
><tr
id=sl_svn7768_459

><td class="source">    float y1 = y_array[1];<br></td></tr
><tr
id=sl_svn7768_460

><td class="source">    float y2 = y_array[2];<br></td></tr
><tr
id=sl_svn7768_461

><td class="source"><br></td></tr
><tr
id=sl_svn7768_462

><td class="source">    //System.out.println(PApplet.hex(m_drawFlags));<br></td></tr
><tr
id=sl_svn7768_463

><td class="source"><br></td></tr
><tr
id=sl_svn7768_464

><td class="source">    // For accurate texture interpolation, need to mark whether<br></td></tr
><tr
id=sl_svn7768_465

><td class="source">    // we&#39;ve already pre-calculated for the triangle<br></td></tr
><tr
id=sl_svn7768_466

><td class="source">    firstSegment = true;<br></td></tr
><tr
id=sl_svn7768_467

><td class="source"><br></td></tr
><tr
id=sl_svn7768_468

><td class="source">    // do backface culling?<br></td></tr
><tr
id=sl_svn7768_469

><td class="source">    if (m_culling) {<br></td></tr
><tr
id=sl_svn7768_470

><td class="source">      x0 = x_array[0];<br></td></tr
><tr
id=sl_svn7768_471

><td class="source">      if ((x_array[2]-x0)*(y1-y0) &lt; (x_array[1]-x0)*(y2-y0))<br></td></tr
><tr
id=sl_svn7768_472

><td class="source">        return;<br></td></tr
><tr
id=sl_svn7768_473

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_474

><td class="source"><br></td></tr
><tr
id=sl_svn7768_475

><td class="source">    /* get vertex order from top -&gt; down */<br></td></tr
><tr
id=sl_svn7768_476

><td class="source">    if (y0 &lt; y1) {<br></td></tr
><tr
id=sl_svn7768_477

><td class="source">      if (y2 &lt; y1) {<br></td></tr
><tr
id=sl_svn7768_478

><td class="source">        if (y2 &lt; y0) { // 2,0,1<br></td></tr
><tr
id=sl_svn7768_479

><td class="source">          o0 = 2;<br></td></tr
><tr
id=sl_svn7768_480

><td class="source">          o1 = 0;<br></td></tr
><tr
id=sl_svn7768_481

><td class="source">          o2 = 1;<br></td></tr
><tr
id=sl_svn7768_482

><td class="source">        } else {  // 0,2,1<br></td></tr
><tr
id=sl_svn7768_483

><td class="source">          o0 = 0;<br></td></tr
><tr
id=sl_svn7768_484

><td class="source">          o1 = 2;<br></td></tr
><tr
id=sl_svn7768_485

><td class="source">          o2 = 1;<br></td></tr
><tr
id=sl_svn7768_486

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_487

><td class="source">      } else {  // 0,1,2<br></td></tr
><tr
id=sl_svn7768_488

><td class="source">        o0 = 0;<br></td></tr
><tr
id=sl_svn7768_489

><td class="source">        o1 = 1;<br></td></tr
><tr
id=sl_svn7768_490

><td class="source">        o2 = 2;<br></td></tr
><tr
id=sl_svn7768_491

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_492

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn7768_493

><td class="source">      if (y2 &gt; y1) {<br></td></tr
><tr
id=sl_svn7768_494

><td class="source">        if (y2 &lt; y0) { // 1,2,0<br></td></tr
><tr
id=sl_svn7768_495

><td class="source">          o0 = 1;<br></td></tr
><tr
id=sl_svn7768_496

><td class="source">          o1 = 2;<br></td></tr
><tr
id=sl_svn7768_497

><td class="source">          o2 = 0;<br></td></tr
><tr
id=sl_svn7768_498

><td class="source">        } else {  // 1,0,2<br></td></tr
><tr
id=sl_svn7768_499

><td class="source">          o0 = 1;<br></td></tr
><tr
id=sl_svn7768_500

><td class="source">          o1 = 0;<br></td></tr
><tr
id=sl_svn7768_501

><td class="source">          o2 = 2;<br></td></tr
><tr
id=sl_svn7768_502

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_503

><td class="source">      } else {  // 2,1,0<br></td></tr
><tr
id=sl_svn7768_504

><td class="source">        o0 = 2;<br></td></tr
><tr
id=sl_svn7768_505

><td class="source">        o1 = 1;<br></td></tr
><tr
id=sl_svn7768_506

><td class="source">        o2 = 0;<br></td></tr
><tr
id=sl_svn7768_507

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_508

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_509

><td class="source"><br></td></tr
><tr
id=sl_svn7768_510

><td class="source">    /**<br></td></tr
><tr
id=sl_svn7768_511

><td class="source">      * o0 = &quot;top&quot; vertex offset<br></td></tr
><tr
id=sl_svn7768_512

><td class="source">      * o1 = &quot;mid&quot; vertex offset<br></td></tr
><tr
id=sl_svn7768_513

><td class="source">      * o2 = &quot;bot&quot; vertex offset<br></td></tr
><tr
id=sl_svn7768_514

><td class="source">     */<br></td></tr
><tr
id=sl_svn7768_515

><td class="source"><br></td></tr
><tr
id=sl_svn7768_516

><td class="source">    y0 = y_array[o0];<br></td></tr
><tr
id=sl_svn7768_517

><td class="source">    int yi0 = (int) (y0 + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_518

><td class="source">    if (yi0 &gt; SCREEN_HEIGHT) {<br></td></tr
><tr
id=sl_svn7768_519

><td class="source">      return;<br></td></tr
><tr
id=sl_svn7768_520

><td class="source">    } else if (yi0 &lt; 0) {<br></td></tr
><tr
id=sl_svn7768_521

><td class="source">      yi0 = 0;<br></td></tr
><tr
id=sl_svn7768_522

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_523

><td class="source"><br></td></tr
><tr
id=sl_svn7768_524

><td class="source">    y2 = y_array[o2];<br></td></tr
><tr
id=sl_svn7768_525

><td class="source">    int yi2 = (int) (y2 + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_526

><td class="source">    if (yi2 &lt; 0) {<br></td></tr
><tr
id=sl_svn7768_527

><td class="source">      return;<br></td></tr
><tr
id=sl_svn7768_528

><td class="source">    } else if (yi2 &gt; SCREEN_HEIGHT) {<br></td></tr
><tr
id=sl_svn7768_529

><td class="source">      yi2 = SCREEN_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_530

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_531

><td class="source"><br></td></tr
><tr
id=sl_svn7768_532

><td class="source">    // Does the poly actually cross a scanline?<br></td></tr
><tr
id=sl_svn7768_533

><td class="source">    if (yi2 &gt; yi0) {<br></td></tr
><tr
id=sl_svn7768_534

><td class="source">      x0 = x_array[o0];<br></td></tr
><tr
id=sl_svn7768_535

><td class="source">      x1 = x_array[o1];<br></td></tr
><tr
id=sl_svn7768_536

><td class="source">      x2 = x_array[o2];<br></td></tr
><tr
id=sl_svn7768_537

><td class="source"><br></td></tr
><tr
id=sl_svn7768_538

><td class="source">      // get mid Y and clip it<br></td></tr
><tr
id=sl_svn7768_539

><td class="source">      y1 = y_array[o1];<br></td></tr
><tr
id=sl_svn7768_540

><td class="source">      int yi1 = (int) (y1 + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_541

><td class="source">      if (yi1 &lt; 0)<br></td></tr
><tr
id=sl_svn7768_542

><td class="source">        yi1 = 0;<br></td></tr
><tr
id=sl_svn7768_543

><td class="source">      if (yi1 &gt; SCREEN_HEIGHT)<br></td></tr
><tr
id=sl_svn7768_544

><td class="source">        yi1 = SCREEN_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_545

><td class="source"><br></td></tr
><tr
id=sl_svn7768_546

><td class="source">      // calculate deltas etc.<br></td></tr
><tr
id=sl_svn7768_547

><td class="source">      dx2 = x2 - x0;<br></td></tr
><tr
id=sl_svn7768_548

><td class="source">      dy0 = y1 - y0;<br></td></tr
><tr
id=sl_svn7768_549

><td class="source">      dy2 = y2 - y0;<br></td></tr
><tr
id=sl_svn7768_550

><td class="source">      xadd2 = dx2 / dy2;  // xadd for &quot;single&quot; edge<br></td></tr
><tr
id=sl_svn7768_551

><td class="source">      temp = dy0 / dy2;<br></td></tr
><tr
id=sl_svn7768_552

><td class="source">      width = temp * dx2 + x0 - x1;<br></td></tr
><tr
id=sl_svn7768_553

><td class="source"><br></td></tr
><tr
id=sl_svn7768_554

><td class="source">      // calculate alpha blend interpolation<br></td></tr
><tr
id=sl_svn7768_555

><td class="source">      if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_556

><td class="source">        a0 = a_array[o0];<br></td></tr
><tr
id=sl_svn7768_557

><td class="source">        a1 = a_array[o1];<br></td></tr
><tr
id=sl_svn7768_558

><td class="source">        a2 = a_array[o2];<br></td></tr
><tr
id=sl_svn7768_559

><td class="source">        da0 = a1-a0;<br></td></tr
><tr
id=sl_svn7768_560

><td class="source">        da2 = a2-a0;<br></td></tr
><tr
id=sl_svn7768_561

><td class="source">        iaadd = (int) ((temp * da2 - da0) / width); // alpha add<br></td></tr
><tr
id=sl_svn7768_562

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_563

><td class="source"><br></td></tr
><tr
id=sl_svn7768_564

><td class="source">      // calculate intensity interpolation<br></td></tr
><tr
id=sl_svn7768_565

><td class="source">      if (INTERPOLATE_RGB) {<br></td></tr
><tr
id=sl_svn7768_566

><td class="source">        r0 = r_array[o0];<br></td></tr
><tr
id=sl_svn7768_567

><td class="source">        r1 = r_array[o1];<br></td></tr
><tr
id=sl_svn7768_568

><td class="source">        r2 = r_array[o2];<br></td></tr
><tr
id=sl_svn7768_569

><td class="source"><br></td></tr
><tr
id=sl_svn7768_570

><td class="source">        g0 = g_array[o0];<br></td></tr
><tr
id=sl_svn7768_571

><td class="source">        g1 = g_array[o1];<br></td></tr
><tr
id=sl_svn7768_572

><td class="source">        g2 = g_array[o2];<br></td></tr
><tr
id=sl_svn7768_573

><td class="source"><br></td></tr
><tr
id=sl_svn7768_574

><td class="source">        b0 = b_array[o0];<br></td></tr
><tr
id=sl_svn7768_575

><td class="source">        b1 = b_array[o1];<br></td></tr
><tr
id=sl_svn7768_576

><td class="source">        b2 = b_array[o2];<br></td></tr
><tr
id=sl_svn7768_577

><td class="source"><br></td></tr
><tr
id=sl_svn7768_578

><td class="source">        dr0 = r1-r0;<br></td></tr
><tr
id=sl_svn7768_579

><td class="source">        dg0 = g1-g0;<br></td></tr
><tr
id=sl_svn7768_580

><td class="source">        db0 = b1-b0;<br></td></tr
><tr
id=sl_svn7768_581

><td class="source"><br></td></tr
><tr
id=sl_svn7768_582

><td class="source">        dr2 = r2-r0;<br></td></tr
><tr
id=sl_svn7768_583

><td class="source">        dg2 = g2-g0;<br></td></tr
><tr
id=sl_svn7768_584

><td class="source">        db2 = b2-b0;<br></td></tr
><tr
id=sl_svn7768_585

><td class="source"><br></td></tr
><tr
id=sl_svn7768_586

><td class="source">        iradd = (int) ((temp * dr2 - dr0) / width); // r add<br></td></tr
><tr
id=sl_svn7768_587

><td class="source">        igadd = (int) ((temp * dg2 - dg0) / width); // g add<br></td></tr
><tr
id=sl_svn7768_588

><td class="source">        ibadd = (int) ((temp * db2 - db0) / width); // b add<br></td></tr
><tr
id=sl_svn7768_589

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_590

><td class="source"><br></td></tr
><tr
id=sl_svn7768_591

><td class="source">      // calculate UV interpolation<br></td></tr
><tr
id=sl_svn7768_592

><td class="source">      if (INTERPOLATE_UV) {<br></td></tr
><tr
id=sl_svn7768_593

><td class="source">        u0 = u_array[o0];<br></td></tr
><tr
id=sl_svn7768_594

><td class="source">        u1 = u_array[o1];<br></td></tr
><tr
id=sl_svn7768_595

><td class="source">        u2 = u_array[o2];<br></td></tr
><tr
id=sl_svn7768_596

><td class="source">        v0 = v_array[o0];<br></td></tr
><tr
id=sl_svn7768_597

><td class="source">        v1 = v_array[o1];<br></td></tr
><tr
id=sl_svn7768_598

><td class="source">        v2 = v_array[o2];<br></td></tr
><tr
id=sl_svn7768_599

><td class="source">        du0 = u1-u0;<br></td></tr
><tr
id=sl_svn7768_600

><td class="source">        dv0 = v1-v0;<br></td></tr
><tr
id=sl_svn7768_601

><td class="source">        du2 = u2-u0;<br></td></tr
><tr
id=sl_svn7768_602

><td class="source">        dv2 = v2-v0;<br></td></tr
><tr
id=sl_svn7768_603

><td class="source">        iuadd = (int) ((temp * du2 - du0) / width); // u add<br></td></tr
><tr
id=sl_svn7768_604

><td class="source">        ivadd = (int) ((temp * dv2 - dv0) / width); // v add<br></td></tr
><tr
id=sl_svn7768_605

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_606

><td class="source"><br></td></tr
><tr
id=sl_svn7768_607

><td class="source">      z0 = z_array[o0];<br></td></tr
><tr
id=sl_svn7768_608

><td class="source">      z1 = z_array[o1];<br></td></tr
><tr
id=sl_svn7768_609

><td class="source">      z2 = z_array[o2];<br></td></tr
><tr
id=sl_svn7768_610

><td class="source">      dz0 = z1-z0;<br></td></tr
><tr
id=sl_svn7768_611

><td class="source">      dz2 = z2-z0;<br></td></tr
><tr
id=sl_svn7768_612

><td class="source">      izadd = (temp * dz2 - dz0) / width;<br></td></tr
><tr
id=sl_svn7768_613

><td class="source"><br></td></tr
><tr
id=sl_svn7768_614

><td class="source">      // draw the upper poly segment if it&#39;s visible<br></td></tr
><tr
id=sl_svn7768_615

><td class="source">      if (yi1 &gt; yi0) {<br></td></tr
><tr
id=sl_svn7768_616

><td class="source">        dta = (yi0 + PIXEL_CENTER) - y0;<br></td></tr
><tr
id=sl_svn7768_617

><td class="source">        xadd1 = (x1 - x0) / dy0;<br></td></tr
><tr
id=sl_svn7768_618

><td class="source"><br></td></tr
><tr
id=sl_svn7768_619

><td class="source">        // we can determine which side is &quot;single&quot; side<br></td></tr
><tr
id=sl_svn7768_620

><td class="source">        // by comparing left/right edge adds<br></td></tr
><tr
id=sl_svn7768_621

><td class="source">        if (xadd2 &gt; xadd1) {<br></td></tr
><tr
id=sl_svn7768_622

><td class="source">          xleft = x0 + dta * xadd1;<br></td></tr
><tr
id=sl_svn7768_623

><td class="source">          xrght = x0 + dta * xadd2;<br></td></tr
><tr
id=sl_svn7768_624

><td class="source">          zleftadd = dz0 / dy0;<br></td></tr
><tr
id=sl_svn7768_625

><td class="source">          zleft = dta*zleftadd+z0;<br></td></tr
><tr
id=sl_svn7768_626

><td class="source"><br></td></tr
><tr
id=sl_svn7768_627

><td class="source">          if (INTERPOLATE_UV) {<br></td></tr
><tr
id=sl_svn7768_628

><td class="source">            uleftadd = du0 / dy0;<br></td></tr
><tr
id=sl_svn7768_629

><td class="source">            vleftadd = dv0 / dy0;<br></td></tr
><tr
id=sl_svn7768_630

><td class="source">            uleft = dta*uleftadd+u0;<br></td></tr
><tr
id=sl_svn7768_631

><td class="source">            vleft = dta*vleftadd+v0;<br></td></tr
><tr
id=sl_svn7768_632

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_633

><td class="source"><br></td></tr
><tr
id=sl_svn7768_634

><td class="source">          if (INTERPOLATE_RGB) {<br></td></tr
><tr
id=sl_svn7768_635

><td class="source">            rleftadd = dr0 / dy0;<br></td></tr
><tr
id=sl_svn7768_636

><td class="source">            gleftadd = dg0 / dy0;<br></td></tr
><tr
id=sl_svn7768_637

><td class="source">            bleftadd = db0 / dy0;<br></td></tr
><tr
id=sl_svn7768_638

><td class="source">            rleft = dta*rleftadd+r0;<br></td></tr
><tr
id=sl_svn7768_639

><td class="source">            gleft = dta*gleftadd+g0;<br></td></tr
><tr
id=sl_svn7768_640

><td class="source">            bleft = dta*bleftadd+b0;<br></td></tr
><tr
id=sl_svn7768_641

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_642

><td class="source"><br></td></tr
><tr
id=sl_svn7768_643

><td class="source">          if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_644

><td class="source">            aleftadd = da0 / dy0;<br></td></tr
><tr
id=sl_svn7768_645

><td class="source">            aleft = dta*aleftadd+a0;<br></td></tr
><tr
id=sl_svn7768_646

><td class="source"><br></td></tr
><tr
id=sl_svn7768_647

><td class="source">            if (m_drawFlags == R_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_648

><td class="source">              drawsegment_plain_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_649

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_650

><td class="source">              drawsegment_gouraud_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_651

><td class="source">            } else if (m_drawFlags == (R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_652

><td class="source">              drawsegment_texture8_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_653

><td class="source">            } else if (m_drawFlags == (R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_654

><td class="source">              drawsegment_texture24_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_655

><td class="source">            } else if (m_drawFlags == (R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_656

><td class="source">              drawsegment_texture32_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_657

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_658

><td class="source">              drawsegment_gouraud_texture8_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_659

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_660

><td class="source">              drawsegment_gouraud_texture24_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_661

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_662

><td class="source">              drawsegment_gouraud_texture32_alpha(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_663

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_664

><td class="source">          } else {<br></td></tr
><tr
id=sl_svn7768_665

><td class="source">            if (m_drawFlags == 0) {<br></td></tr
><tr
id=sl_svn7768_666

><td class="source">              drawsegment_plain(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_667

><td class="source">            } else if (m_drawFlags == R_GOURAUD) {<br></td></tr
><tr
id=sl_svn7768_668

><td class="source">              drawsegment_gouraud(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_669

><td class="source">            } else if (m_drawFlags == R_TEXTURE8) {<br></td></tr
><tr
id=sl_svn7768_670

><td class="source">              drawsegment_texture8(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_671

><td class="source">            } else if (m_drawFlags == R_TEXTURE24) {<br></td></tr
><tr
id=sl_svn7768_672

><td class="source">              drawsegment_texture24(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_673

><td class="source">            } else if (m_drawFlags == R_TEXTURE32) {<br></td></tr
><tr
id=sl_svn7768_674

><td class="source">              drawsegment_texture32(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_675

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8)) {<br></td></tr
><tr
id=sl_svn7768_676

><td class="source">              drawsegment_gouraud_texture8(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_677

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24)) {<br></td></tr
><tr
id=sl_svn7768_678

><td class="source">              drawsegment_gouraud_texture24(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_679

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32)) {<br></td></tr
><tr
id=sl_svn7768_680

><td class="source">              drawsegment_gouraud_texture32(xadd1,xadd2, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_681

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_682

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_683

><td class="source">          m_singleRight = true;<br></td></tr
><tr
id=sl_svn7768_684

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_685

><td class="source">          xleft = x0 + dta * xadd2;<br></td></tr
><tr
id=sl_svn7768_686

><td class="source">          xrght = x0 + dta * xadd1;<br></td></tr
><tr
id=sl_svn7768_687

><td class="source">          zleftadd = dz2 / dy2;<br></td></tr
><tr
id=sl_svn7768_688

><td class="source">          zleft = dta*zleftadd+z0;<br></td></tr
><tr
id=sl_svn7768_689

><td class="source">          //<br></td></tr
><tr
id=sl_svn7768_690

><td class="source">          if (INTERPOLATE_UV) {<br></td></tr
><tr
id=sl_svn7768_691

><td class="source">            uleftadd = du2 / dy2;<br></td></tr
><tr
id=sl_svn7768_692

><td class="source">            vleftadd = dv2 / dy2;<br></td></tr
><tr
id=sl_svn7768_693

><td class="source">            uleft = dta*uleftadd+u0;<br></td></tr
><tr
id=sl_svn7768_694

><td class="source">            vleft = dta*vleftadd+v0;<br></td></tr
><tr
id=sl_svn7768_695

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_696

><td class="source"><br></td></tr
><tr
id=sl_svn7768_697

><td class="source">          //<br></td></tr
><tr
id=sl_svn7768_698

><td class="source">          if (INTERPOLATE_RGB) {<br></td></tr
><tr
id=sl_svn7768_699

><td class="source">            rleftadd = dr2 / dy2;<br></td></tr
><tr
id=sl_svn7768_700

><td class="source">            gleftadd = dg2 / dy2;<br></td></tr
><tr
id=sl_svn7768_701

><td class="source">            bleftadd = db2 / dy2;<br></td></tr
><tr
id=sl_svn7768_702

><td class="source">            rleft = dta*rleftadd+r0;<br></td></tr
><tr
id=sl_svn7768_703

><td class="source">            gleft = dta*gleftadd+g0;<br></td></tr
><tr
id=sl_svn7768_704

><td class="source">            bleft = dta*bleftadd+b0;<br></td></tr
><tr
id=sl_svn7768_705

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_706

><td class="source"><br></td></tr
><tr
id=sl_svn7768_707

><td class="source"><br></td></tr
><tr
id=sl_svn7768_708

><td class="source">          if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_709

><td class="source">            aleftadd = da2 / dy2;<br></td></tr
><tr
id=sl_svn7768_710

><td class="source">            aleft = dta*aleftadd+a0;<br></td></tr
><tr
id=sl_svn7768_711

><td class="source"><br></td></tr
><tr
id=sl_svn7768_712

><td class="source">            if (m_drawFlags == R_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_713

><td class="source">              drawsegment_plain_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_714

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_715

><td class="source">              drawsegment_gouraud_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_716

><td class="source">            } else if (m_drawFlags == (R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_717

><td class="source">              drawsegment_texture8_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_718

><td class="source">            } else if (m_drawFlags == (R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_719

><td class="source">              drawsegment_texture24_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_720

><td class="source">            } else if (m_drawFlags == (R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_721

><td class="source">              drawsegment_texture32_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_722

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_723

><td class="source">              drawsegment_gouraud_texture8_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_724

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_725

><td class="source">              drawsegment_gouraud_texture24_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_726

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_727

><td class="source">              drawsegment_gouraud_texture32_alpha(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_728

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_729

><td class="source">          } else {<br></td></tr
><tr
id=sl_svn7768_730

><td class="source">            if (m_drawFlags == 0) {<br></td></tr
><tr
id=sl_svn7768_731

><td class="source">              drawsegment_plain(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_732

><td class="source">            } else if (m_drawFlags == R_GOURAUD) {<br></td></tr
><tr
id=sl_svn7768_733

><td class="source">              drawsegment_gouraud(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_734

><td class="source">            } else if (m_drawFlags == R_TEXTURE8) {<br></td></tr
><tr
id=sl_svn7768_735

><td class="source">              drawsegment_texture8(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_736

><td class="source">            } else if (m_drawFlags == R_TEXTURE24) {<br></td></tr
><tr
id=sl_svn7768_737

><td class="source">              drawsegment_texture24(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_738

><td class="source">            } else if (m_drawFlags == R_TEXTURE32) {<br></td></tr
><tr
id=sl_svn7768_739

><td class="source">              drawsegment_texture32(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_740

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8)) {<br></td></tr
><tr
id=sl_svn7768_741

><td class="source">              drawsegment_gouraud_texture8(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_742

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24)) {<br></td></tr
><tr
id=sl_svn7768_743

><td class="source">              drawsegment_gouraud_texture24(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_744

><td class="source">            } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32)) {<br></td></tr
><tr
id=sl_svn7768_745

><td class="source">              drawsegment_gouraud_texture32(xadd2, xadd1, yi0,yi1);<br></td></tr
><tr
id=sl_svn7768_746

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_747

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_748

><td class="source">          m_singleRight = false;<br></td></tr
><tr
id=sl_svn7768_749

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_750

><td class="source"><br></td></tr
><tr
id=sl_svn7768_751

><td class="source">        // if bottom segment height is zero, return<br></td></tr
><tr
id=sl_svn7768_752

><td class="source">        if (yi2 == yi1) return;<br></td></tr
><tr
id=sl_svn7768_753

><td class="source"><br></td></tr
><tr
id=sl_svn7768_754

><td class="source">        // calculate xadd 1<br></td></tr
><tr
id=sl_svn7768_755

><td class="source">        dy1 = y2 - y1;<br></td></tr
><tr
id=sl_svn7768_756

><td class="source">        xadd1 = (x2 - x1) / dy1;<br></td></tr
><tr
id=sl_svn7768_757

><td class="source"><br></td></tr
><tr
id=sl_svn7768_758

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_759

><td class="source">        // top seg height was zero, calculate &amp; clip single edge X<br></td></tr
><tr
id=sl_svn7768_760

><td class="source">        dy1 = y2 - y1;<br></td></tr
><tr
id=sl_svn7768_761

><td class="source">        xadd1 = (x2 - x1) / dy1;<br></td></tr
><tr
id=sl_svn7768_762

><td class="source"><br></td></tr
><tr
id=sl_svn7768_763

><td class="source">        // which edge is left?<br></td></tr
><tr
id=sl_svn7768_764

><td class="source">        if (xadd2 &lt; xadd1) {<br></td></tr
><tr
id=sl_svn7768_765

><td class="source">          xrght = ((yi1 + PIXEL_CENTER) - y0) * xadd2 + x0;<br></td></tr
><tr
id=sl_svn7768_766

><td class="source">          m_singleRight = true;<br></td></tr
><tr
id=sl_svn7768_767

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_768

><td class="source">          dta = (yi1 + PIXEL_CENTER) - y0;<br></td></tr
><tr
id=sl_svn7768_769

><td class="source">          xleft = dta * xadd2 + x0;<br></td></tr
><tr
id=sl_svn7768_770

><td class="source">          zleftadd = dz2 / dy2;<br></td></tr
><tr
id=sl_svn7768_771

><td class="source">          zleft = dta * zleftadd + z0;<br></td></tr
><tr
id=sl_svn7768_772

><td class="source"><br></td></tr
><tr
id=sl_svn7768_773

><td class="source">          if (INTERPOLATE_UV) {<br></td></tr
><tr
id=sl_svn7768_774

><td class="source">            uleftadd = du2 / dy2;<br></td></tr
><tr
id=sl_svn7768_775

><td class="source">            vleftadd = dv2 / dy2;<br></td></tr
><tr
id=sl_svn7768_776

><td class="source">            uleft = dta * uleftadd + u0;<br></td></tr
><tr
id=sl_svn7768_777

><td class="source">            vleft = dta * vleftadd + v0;<br></td></tr
><tr
id=sl_svn7768_778

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_779

><td class="source"><br></td></tr
><tr
id=sl_svn7768_780

><td class="source">          if (INTERPOLATE_RGB) {<br></td></tr
><tr
id=sl_svn7768_781

><td class="source">            rleftadd = dr2 / dy2;<br></td></tr
><tr
id=sl_svn7768_782

><td class="source">            gleftadd = dg2 / dy2;<br></td></tr
><tr
id=sl_svn7768_783

><td class="source">            bleftadd = db2 / dy2;<br></td></tr
><tr
id=sl_svn7768_784

><td class="source">            rleft = dta * rleftadd + r0;<br></td></tr
><tr
id=sl_svn7768_785

><td class="source">            gleft = dta * gleftadd + g0;<br></td></tr
><tr
id=sl_svn7768_786

><td class="source">            bleft = dta * bleftadd + b0;<br></td></tr
><tr
id=sl_svn7768_787

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_788

><td class="source"><br></td></tr
><tr
id=sl_svn7768_789

><td class="source">          //<br></td></tr
><tr
id=sl_svn7768_790

><td class="source">          if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_791

><td class="source">            aleftadd = da2 / dy2;<br></td></tr
><tr
id=sl_svn7768_792

><td class="source">            aleft = dta * aleftadd + a0;<br></td></tr
><tr
id=sl_svn7768_793

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_794

><td class="source">          m_singleRight = false;<br></td></tr
><tr
id=sl_svn7768_795

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_796

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_797

><td class="source"><br></td></tr
><tr
id=sl_svn7768_798

><td class="source">      // draw the lower segment<br></td></tr
><tr
id=sl_svn7768_799

><td class="source">      if (m_singleRight) {<br></td></tr
><tr
id=sl_svn7768_800

><td class="source">        dta = (yi1 + PIXEL_CENTER) - y1;<br></td></tr
><tr
id=sl_svn7768_801

><td class="source">        xleft = dta * xadd1 + x1;<br></td></tr
><tr
id=sl_svn7768_802

><td class="source">        zleftadd = (z2 - z1) / dy1;<br></td></tr
><tr
id=sl_svn7768_803

><td class="source">        zleft = dta * zleftadd + z1;<br></td></tr
><tr
id=sl_svn7768_804

><td class="source"><br></td></tr
><tr
id=sl_svn7768_805

><td class="source">        if (INTERPOLATE_UV) {<br></td></tr
><tr
id=sl_svn7768_806

><td class="source">          uleftadd = (u2 - u1) / dy1;<br></td></tr
><tr
id=sl_svn7768_807

><td class="source">          vleftadd = (v2 - v1) / dy1;<br></td></tr
><tr
id=sl_svn7768_808

><td class="source">          uleft = dta * uleftadd + u1;<br></td></tr
><tr
id=sl_svn7768_809

><td class="source">          vleft = dta * vleftadd + v1;<br></td></tr
><tr
id=sl_svn7768_810

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_811

><td class="source"><br></td></tr
><tr
id=sl_svn7768_812

><td class="source">        if (INTERPOLATE_RGB) {<br></td></tr
><tr
id=sl_svn7768_813

><td class="source">          rleftadd = (r2 - r1) / dy1;<br></td></tr
><tr
id=sl_svn7768_814

><td class="source">          gleftadd = (g2 - g1) / dy1;<br></td></tr
><tr
id=sl_svn7768_815

><td class="source">          bleftadd = (b2 - b1) / dy1;<br></td></tr
><tr
id=sl_svn7768_816

><td class="source">          rleft = dta * rleftadd + r1;<br></td></tr
><tr
id=sl_svn7768_817

><td class="source">          gleft = dta * gleftadd + g1;<br></td></tr
><tr
id=sl_svn7768_818

><td class="source">          bleft = dta * bleftadd + b1;<br></td></tr
><tr
id=sl_svn7768_819

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_820

><td class="source"><br></td></tr
><tr
id=sl_svn7768_821

><td class="source">        if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_822

><td class="source">          aleftadd = (a2 - a1) / dy1;<br></td></tr
><tr
id=sl_svn7768_823

><td class="source">          aleft = dta * aleftadd + a1;<br></td></tr
><tr
id=sl_svn7768_824

><td class="source"><br></td></tr
><tr
id=sl_svn7768_825

><td class="source">          if (m_drawFlags == R_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_826

><td class="source">            drawsegment_plain_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_827

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_828

><td class="source">            drawsegment_gouraud_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_829

><td class="source">          } else if (m_drawFlags == (R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_830

><td class="source">            drawsegment_texture8_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_831

><td class="source">          } else if (m_drawFlags == (R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_832

><td class="source">            drawsegment_texture24_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_833

><td class="source">          } else if (m_drawFlags == (R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_834

><td class="source">            drawsegment_texture32_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_835

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_836

><td class="source">            drawsegment_gouraud_texture8_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_837

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_838

><td class="source">            drawsegment_gouraud_texture24_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_839

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_840

><td class="source">            drawsegment_gouraud_texture32_alpha(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_841

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_842

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_843

><td class="source">          if (m_drawFlags == 0) {<br></td></tr
><tr
id=sl_svn7768_844

><td class="source">            drawsegment_plain(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_845

><td class="source">          } else if (m_drawFlags == R_GOURAUD) {<br></td></tr
><tr
id=sl_svn7768_846

><td class="source">            drawsegment_gouraud(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_847

><td class="source">          } else if (m_drawFlags == R_TEXTURE8) {<br></td></tr
><tr
id=sl_svn7768_848

><td class="source">            drawsegment_texture8(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_849

><td class="source">          } else if (m_drawFlags == R_TEXTURE24) {<br></td></tr
><tr
id=sl_svn7768_850

><td class="source">            drawsegment_texture24(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_851

><td class="source">          } else if (m_drawFlags == R_TEXTURE32) {<br></td></tr
><tr
id=sl_svn7768_852

><td class="source">            drawsegment_texture32(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_853

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8)) {<br></td></tr
><tr
id=sl_svn7768_854

><td class="source">            drawsegment_gouraud_texture8(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_855

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24)) {<br></td></tr
><tr
id=sl_svn7768_856

><td class="source">            drawsegment_gouraud_texture24(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_857

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32)) {<br></td></tr
><tr
id=sl_svn7768_858

><td class="source">            drawsegment_gouraud_texture32(xadd1, xadd2, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_859

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_860

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_861

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_862

><td class="source">        xrght = ((yi1 + PIXEL_CENTER)- y1) * xadd1 + x1;<br></td></tr
><tr
id=sl_svn7768_863

><td class="source"><br></td></tr
><tr
id=sl_svn7768_864

><td class="source">        if (INTERPOLATE_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_865

><td class="source">          if (m_drawFlags == R_ALPHA) {<br></td></tr
><tr
id=sl_svn7768_866

><td class="source">            drawsegment_plain_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_867

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_868

><td class="source">            drawsegment_gouraud_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_869

><td class="source">          } else if (m_drawFlags == (R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_870

><td class="source">            drawsegment_texture8_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_871

><td class="source">          } else if (m_drawFlags == (R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_872

><td class="source">            drawsegment_texture24_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_873

><td class="source">          } else if (m_drawFlags == (R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_874

><td class="source">            drawsegment_texture32_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_875

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_876

><td class="source">            drawsegment_gouraud_texture8_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_877

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_878

><td class="source">            drawsegment_gouraud_texture24_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_879

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32 + R_ALPHA)) {<br></td></tr
><tr
id=sl_svn7768_880

><td class="source">            drawsegment_gouraud_texture32_alpha(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_881

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_882

><td class="source">        } else {<br></td></tr
><tr
id=sl_svn7768_883

><td class="source">          if (m_drawFlags == 0) {<br></td></tr
><tr
id=sl_svn7768_884

><td class="source">            drawsegment_plain(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_885

><td class="source">          } else if (m_drawFlags == R_GOURAUD) {<br></td></tr
><tr
id=sl_svn7768_886

><td class="source">            drawsegment_gouraud(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_887

><td class="source">          } else if (m_drawFlags == R_TEXTURE8) {<br></td></tr
><tr
id=sl_svn7768_888

><td class="source">            drawsegment_texture8(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_889

><td class="source">          } else if (m_drawFlags == R_TEXTURE24) {<br></td></tr
><tr
id=sl_svn7768_890

><td class="source">            drawsegment_texture24(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_891

><td class="source">          } else if (m_drawFlags == R_TEXTURE32) {<br></td></tr
><tr
id=sl_svn7768_892

><td class="source">            drawsegment_texture32(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_893

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE8)) {<br></td></tr
><tr
id=sl_svn7768_894

><td class="source">            drawsegment_gouraud_texture8(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_895

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE24)) {<br></td></tr
><tr
id=sl_svn7768_896

><td class="source">            drawsegment_gouraud_texture24(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_897

><td class="source">          } else if (m_drawFlags == (R_GOURAUD + R_TEXTURE32)) {<br></td></tr
><tr
id=sl_svn7768_898

><td class="source">            drawsegment_gouraud_texture32(xadd2, xadd1, yi1,yi2);<br></td></tr
><tr
id=sl_svn7768_899

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_900

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_901

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_902

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_903

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_904

><td class="source"><br></td></tr
><tr
id=sl_svn7768_905

><td class="source"><br></td></tr
><tr
id=sl_svn7768_906

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_907

><td class="source">   * Accurate texturing code by ewjordan@gmail.com, April 14, 2007<br></td></tr
><tr
id=sl_svn7768_908

><td class="source">   * The getColorFromTexture() function should be inlined and optimized<br></td></tr
><tr
id=sl_svn7768_909

><td class="source">   * so that most of the heavy lifting happens outside the per-pixel loop.<br></td></tr
><tr
id=sl_svn7768_910

><td class="source">   * The unoptimized generic algorithm looks like this (unless noted,<br></td></tr
><tr
id=sl_svn7768_911

><td class="source">   * all of these variables are vectors, so the actual code will look messier):<br></td></tr
><tr
id=sl_svn7768_912

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_913

><td class="source">   * p = camera space vector where u == 0, v == 0;<br></td></tr
><tr
id=sl_svn7768_914

><td class="source">   * m = vector from p to location where u == TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_915

><td class="source">   * n = vector from p to location where v == TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_916

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_917

><td class="source">   * A = p cross n;<br></td></tr
><tr
id=sl_svn7768_918

><td class="source">   * B = m cross p;<br></td></tr
><tr
id=sl_svn7768_919

><td class="source">   * C = n cross m;<br></td></tr
><tr
id=sl_svn7768_920

><td class="source">   * A *= texture.width;<br></td></tr
><tr
id=sl_svn7768_921

><td class="source">   * B *= texture.height;<br></td></tr
><tr
id=sl_svn7768_922

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_923

><td class="source">   * for (scanlines in triangle){<br></td></tr
><tr
id=sl_svn7768_924

><td class="source">   *   float a = S * A;<br></td></tr
><tr
id=sl_svn7768_925

><td class="source">   *   float b = S * B;<br></td></tr
><tr
id=sl_svn7768_926

><td class="source">   *   float c = S * C;<br></td></tr
><tr
id=sl_svn7768_927

><td class="source">   *   for (pixels in scanline){<br></td></tr
><tr
id=sl_svn7768_928

><td class="source">   *     int u = a/c;<br></td></tr
><tr
id=sl_svn7768_929

><td class="source">   *     int v = b/c;<br></td></tr
><tr
id=sl_svn7768_930

><td class="source">   *     color = texture[v * texture.width + u];<br></td></tr
><tr
id=sl_svn7768_931

><td class="source">   *     a += A.x;<br></td></tr
><tr
id=sl_svn7768_932

><td class="source">   *     b += B.x;<br></td></tr
><tr
id=sl_svn7768_933

><td class="source">   *     c += C.x;<br></td></tr
><tr
id=sl_svn7768_934

><td class="source">   *   }<br></td></tr
><tr
id=sl_svn7768_935

><td class="source">   * }<br></td></tr
><tr
id=sl_svn7768_936

><td class="source">   *<br></td></tr
><tr
id=sl_svn7768_937

><td class="source">   * We don&#39;t use this exact algorithm here, however, because of the extra<br></td></tr
><tr
id=sl_svn7768_938

><td class="source">   * overhead from the divides. Instead we compute the exact u and v (labelled<br></td></tr
><tr
id=sl_svn7768_939

><td class="source">   * iu and iv in the code) at the start of each scanline and we perform a<br></td></tr
><tr
id=sl_svn7768_940

><td class="source">   * linear interpolation for every linearInterpLength = 1 &lt;&lt; TEX_INTERP_POWER<br></td></tr
><tr
id=sl_svn7768_941

><td class="source">   * pixels. This means that we only perform the true calculation once in a<br></td></tr
><tr
id=sl_svn7768_942

><td class="source">   * while, and the rest of the time the algorithm functions exactly as in the<br></td></tr
><tr
id=sl_svn7768_943

><td class="source">   * fast inaccurate case, at least in theory.  In practice, even if we set<br></td></tr
><tr
id=sl_svn7768_944

><td class="source">   * linearInterpLength very high we still incur some speed penalty due to the<br></td></tr
><tr
id=sl_svn7768_945

><td class="source">   * preprocessing that must take place per-scanline.  A similar method could<br></td></tr
><tr
id=sl_svn7768_946

><td class="source">   * be applied per scanline to avoid this, but it would only be worthwhile in<br></td></tr
><tr
id=sl_svn7768_947

><td class="source">   * the case that we never compute more than one exact calculation per<br></td></tr
><tr
id=sl_svn7768_948

><td class="source">   * scanline.  If we want something like this, however, it would be best to<br></td></tr
><tr
id=sl_svn7768_949

><td class="source">   * create another mode of calculation called &quot;constant-z&quot; interpolation,<br></td></tr
><tr
id=sl_svn7768_950

><td class="source">   * which could be used for things like floors and ceilings where the<br></td></tr
><tr
id=sl_svn7768_951

><td class="source">   * distance from the camera plane never changes over the course of a<br></td></tr
><tr
id=sl_svn7768_952

><td class="source">   * scanline.  We could also add the vertical analogue for drawing vertical<br></td></tr
><tr
id=sl_svn7768_953

><td class="source">   * walls.  In any case, these are not critical as the current algorithm runs<br></td></tr
><tr
id=sl_svn7768_954

><td class="source">   * fairly well, perhaps ~10% slower than the default perspective-less one.<br></td></tr
><tr
id=sl_svn7768_955

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_956

><td class="source"><br></td></tr
><tr
id=sl_svn7768_957

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_958

><td class="source">   * Solve for camera space coordinates of critical texture points and<br></td></tr
><tr
id=sl_svn7768_959

><td class="source">   * set up per-triangle variables for accurate texturing.<br></td></tr
><tr
id=sl_svn7768_960

><td class="source">   * Sets all class variables relevant to accurate texture computation<br></td></tr
><tr
id=sl_svn7768_961

><td class="source">   * Should be called once per triangle - checks firstSegment to see if<br></td></tr
><tr
id=sl_svn7768_962

><td class="source">   * we&#39;ve already called.<br></td></tr
><tr
id=sl_svn7768_963

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_964

><td class="source">  private boolean precomputeAccurateTexturing() {<br></td></tr
><tr
id=sl_svn7768_965

><td class="source">    // rescale u/v_array values when inverting matrix and performing other calcs<br></td></tr
><tr
id=sl_svn7768_966

><td class="source">    float myFact = 65500.0f;<br></td></tr
><tr
id=sl_svn7768_967

><td class="source">    float myFact2 = 65500.0f;<br></td></tr
><tr
id=sl_svn7768_968

><td class="source"><br></td></tr
><tr
id=sl_svn7768_969

><td class="source">    //Matrix inversion to find affine transform between (u,v,(1)) -&gt; (x,y,z)<br></td></tr
><tr
id=sl_svn7768_970

><td class="source"><br></td></tr
><tr
id=sl_svn7768_971

><td class="source">    // OPTIMIZE: There should be a way to avoid the inversion here, which is<br></td></tr
><tr
id=sl_svn7768_972

><td class="source">    // quite expensive (~150 mults).  Also it might crap out due to loss of<br></td></tr
><tr
id=sl_svn7768_973

><td class="source">    // precision depending on the scaling of the u/v_arrays.  Nothing clever<br></td></tr
><tr
id=sl_svn7768_974

><td class="source">    // currently happens if the inversion fails, since this means the<br></td></tr
><tr
id=sl_svn7768_975

><td class="source">    // transformation is degenerate - we just pass false back to the caller<br></td></tr
><tr
id=sl_svn7768_976

><td class="source">    // and let it handle the situation. [There is no good solution to this<br></td></tr
><tr
id=sl_svn7768_977

><td class="source">    // case from within this function, since the way the calculation proceeds<br></td></tr
><tr
id=sl_svn7768_978

><td class="source">    // presumes a non-degenerate transformation matrix between camera space<br></td></tr
><tr
id=sl_svn7768_979

><td class="source">    // and uv space]<br></td></tr
><tr
id=sl_svn7768_980

><td class="source"><br></td></tr
><tr
id=sl_svn7768_981

><td class="source">    // Obvious optimization: if the vertices are actually at the appropriate<br></td></tr
><tr
id=sl_svn7768_982

><td class="source">    // texture coordinates (e.g. (0,0), (TEX_WIDTH,0), and (0,TEX_HEIGHT))<br></td></tr
><tr
id=sl_svn7768_983

><td class="source">    // then we can immediately return the right solution without the inversion.<br></td></tr
><tr
id=sl_svn7768_984

><td class="source">    // This is fairly common, so could speed up many cases of drawing.<br></td></tr
><tr
id=sl_svn7768_985

><td class="source">    // [not implemented]<br></td></tr
><tr
id=sl_svn7768_986

><td class="source"><br></td></tr
><tr
id=sl_svn7768_987

><td class="source">    // Furthermore, we could cache the p,resultT0,result0T vectors in the<br></td></tr
><tr
id=sl_svn7768_988

><td class="source">    // triangle&#39;s basis, since we could then do a look-up and generate the<br></td></tr
><tr
id=sl_svn7768_989

><td class="source">    // resulting coordinates very simply. This would include the above<br></td></tr
><tr
id=sl_svn7768_990

><td class="source">    // optimization as a special case - we could pre-populate the cache with<br></td></tr
><tr
id=sl_svn7768_991

><td class="source">    // special cases like that and dynamically add more. The idea here is that<br></td></tr
><tr
id=sl_svn7768_992

><td class="source">    // most people simply paste textures onto triangles and move the triangles<br></td></tr
><tr
id=sl_svn7768_993

><td class="source">    // from frame to frame, so any per-triangle-per-frame code is likely<br></td></tr
><tr
id=sl_svn7768_994

><td class="source">    // wasted effort. [not implemented]<br></td></tr
><tr
id=sl_svn7768_995

><td class="source"><br></td></tr
><tr
id=sl_svn7768_996

><td class="source">    // Note: o0, o1, and o2 vary depending on view angle to triangle,<br></td></tr
><tr
id=sl_svn7768_997

><td class="source">    // but p, n, and m should not depend on ordering differences<br></td></tr
><tr
id=sl_svn7768_998

><td class="source"><br></td></tr
><tr
id=sl_svn7768_999

><td class="source">    if (firstSegment){<br></td></tr
><tr
id=sl_svn7768_1000

><td class="source">      PMatrix3D myMatrix = <br></td></tr
><tr
id=sl_svn7768_1001

><td class="source">        new PMatrix3D(u_array[o0]/myFact, v_array[o0]/myFact2, 1, 0,<br></td></tr
><tr
id=sl_svn7768_1002

><td class="source">                    u_array[o1]/myFact, v_array[o1]/myFact2, 1, 0,<br></td></tr
><tr
id=sl_svn7768_1003

><td class="source">                    u_array[o2]/myFact, v_array[o2]/myFact2, 1, 0,<br></td></tr
><tr
id=sl_svn7768_1004

><td class="source">                    0,           0,           0, 1);<br></td></tr
><tr
id=sl_svn7768_1005

><td class="source">      // A 3x3 inversion would be more efficient here, <br></td></tr
><tr
id=sl_svn7768_1006

><td class="source">      // given that the fourth r/c are unity<br></td></tr
><tr
id=sl_svn7768_1007

><td class="source">      // if the matrix inversion had trouble, let the caller know<br></td></tr
><tr
id=sl_svn7768_1008

><td class="source">      if (!myMatrix.invert()) return false;<br></td></tr
><tr
id=sl_svn7768_1009

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1010

><td class="source">      float m00, m01, m02, m10, m11, m12, m20, m21, m22;<br></td></tr
><tr
id=sl_svn7768_1011

><td class="source">      m00 = myMatrix.m00*camX[o0]+myMatrix.m01*camX[o1]+myMatrix.m02*camX[o2];<br></td></tr
><tr
id=sl_svn7768_1012

><td class="source">      m01 = myMatrix.m10*camX[o0]+myMatrix.m11*camX[o1]+myMatrix.m12*camX[o2];<br></td></tr
><tr
id=sl_svn7768_1013

><td class="source">      m02 = myMatrix.m20*camX[o0]+myMatrix.m21*camX[o1]+myMatrix.m22*camX[o2];<br></td></tr
><tr
id=sl_svn7768_1014

><td class="source">      m10 = myMatrix.m00*camY[o0]+myMatrix.m01*camY[o1]+myMatrix.m02*camY[o2];<br></td></tr
><tr
id=sl_svn7768_1015

><td class="source">      m11 = myMatrix.m10*camY[o0]+myMatrix.m11*camY[o1]+myMatrix.m12*camY[o2];<br></td></tr
><tr
id=sl_svn7768_1016

><td class="source">      m12 = myMatrix.m20*camY[o0]+myMatrix.m21*camY[o1]+myMatrix.m22*camY[o2];<br></td></tr
><tr
id=sl_svn7768_1017

><td class="source">      m20 = -(myMatrix.m00*camZ[o0]+myMatrix.m01*camZ[o1]+myMatrix.m02*camZ[o2]);<br></td></tr
><tr
id=sl_svn7768_1018

><td class="source">      m21 = -(myMatrix.m10*camZ[o0]+myMatrix.m11*camZ[o1]+myMatrix.m12*camZ[o2]);<br></td></tr
><tr
id=sl_svn7768_1019

><td class="source">      m22 = -(myMatrix.m20*camZ[o0]+myMatrix.m21*camZ[o1]+myMatrix.m22*camZ[o2]);<br></td></tr
><tr
id=sl_svn7768_1020

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1021

><td class="source">      float px = m02;<br></td></tr
><tr
id=sl_svn7768_1022

><td class="source">      float py = m12;<br></td></tr
><tr
id=sl_svn7768_1023

><td class="source">      float pz = m22;<br></td></tr
><tr
id=sl_svn7768_1024

><td class="source">      // Bugfix: possibly we should use F_TEX_WIDTH/HEIGHT instead?<br></td></tr
><tr
id=sl_svn7768_1025

><td class="source">      // Seems to read off end of array in that case, though...<br></td></tr
><tr
id=sl_svn7768_1026

><td class="source">      float resultT0x = m00*TEX_WIDTH+m02;<br></td></tr
><tr
id=sl_svn7768_1027

><td class="source">      float resultT0y = m10*TEX_WIDTH+m12;<br></td></tr
><tr
id=sl_svn7768_1028

><td class="source">      float resultT0z = m20*TEX_WIDTH+m22;<br></td></tr
><tr
id=sl_svn7768_1029

><td class="source">      float result0Tx = m01*TEX_HEIGHT+m02;<br></td></tr
><tr
id=sl_svn7768_1030

><td class="source">      float result0Ty = m11*TEX_HEIGHT+m12;<br></td></tr
><tr
id=sl_svn7768_1031

><td class="source">      float result0Tz = m21*TEX_HEIGHT+m22;<br></td></tr
><tr
id=sl_svn7768_1032

><td class="source">      float mx = resultT0x-m02;<br></td></tr
><tr
id=sl_svn7768_1033

><td class="source">      float my = resultT0y-m12;<br></td></tr
><tr
id=sl_svn7768_1034

><td class="source">      float mz = resultT0z-m22;<br></td></tr
><tr
id=sl_svn7768_1035

><td class="source">      float nx = result0Tx-m02;<br></td></tr
><tr
id=sl_svn7768_1036

><td class="source">      float ny = result0Ty-m12;<br></td></tr
><tr
id=sl_svn7768_1037

><td class="source">      float nz = result0Tz-m22;<br></td></tr
><tr
id=sl_svn7768_1038

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1039

><td class="source">      //avec = p x n<br></td></tr
><tr
id=sl_svn7768_1040

><td class="source">      ax = (py*nz-pz*ny)*TEX_WIDTH; //F_TEX_WIDTH/HEIGHT?<br></td></tr
><tr
id=sl_svn7768_1041

><td class="source">      ay = (pz*nx-px*nz)*TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1042

><td class="source">      az = (px*ny-py*nx)*TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1043

><td class="source">      //bvec = m x p<br></td></tr
><tr
id=sl_svn7768_1044

><td class="source">      bx = (my*pz-mz*py)*TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_1045

><td class="source">      by = (mz*px-mx*pz)*TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_1046

><td class="source">      bz = (mx*py-my*px)*TEX_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_1047

><td class="source">      //cvec = n x m<br></td></tr
><tr
id=sl_svn7768_1048

><td class="source">      cx = ny*mz-nz*my;<br></td></tr
><tr
id=sl_svn7768_1049

><td class="source">      cy = nz*mx-nx*mz;<br></td></tr
><tr
id=sl_svn7768_1050

><td class="source">      cz = nx*my-ny*mx;<br></td></tr
><tr
id=sl_svn7768_1051

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1052

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1053

><td class="source">    nearPlaneWidth = parent.rightScreen-parent.leftScreen;<br></td></tr
><tr
id=sl_svn7768_1054

><td class="source">    nearPlaneHeight = parent.topScreen-parent.bottomScreen;<br></td></tr
><tr
id=sl_svn7768_1055

><td class="source">    nearPlaneDepth = parent.nearPlane;<br></td></tr
><tr
id=sl_svn7768_1056

><td class="source">    // one pixel width in nearPlane coordinates<br></td></tr
><tr
id=sl_svn7768_1057

><td class="source">    xmult = nearPlaneWidth / SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1058

><td class="source">    ymult = nearPlaneHeight / SCREEN_HEIGHT;<br></td></tr
><tr
id=sl_svn7768_1059

><td class="source">    // Extra scalings to map screen plane units to pixel units<br></td></tr
><tr
id=sl_svn7768_1060

><td class="source">    newax = ax*xmult;<br></td></tr
><tr
id=sl_svn7768_1061

><td class="source">    newbx = bx*xmult;<br></td></tr
><tr
id=sl_svn7768_1062

><td class="source">    newcx = cx*xmult;<br></td></tr
><tr
id=sl_svn7768_1063

><td class="source">    return true;<br></td></tr
><tr
id=sl_svn7768_1064

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1065

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1066

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1067

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1068

><td class="source">   * Set the power of two used for linear interpolation of texture coordinates.<br></td></tr
><tr
id=sl_svn7768_1069

><td class="source">   * A true texture coordinate is computed every 2^pwr pixels along a scanline.<br></td></tr
><tr
id=sl_svn7768_1070

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1071

><td class="source">  static public void setInterpPower(int pwr) {<br></td></tr
><tr
id=sl_svn7768_1072

><td class="source">    //Currently must be invoked from P5 as PTriangle.setInterpPower(...)<br></td></tr
><tr
id=sl_svn7768_1073

><td class="source">    TEX_INTERP_POWER = pwr;<br></td></tr
><tr
id=sl_svn7768_1074

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1075

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1076

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1077

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1078

><td class="source">   * Plain color<br></td></tr
><tr
id=sl_svn7768_1079

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1080

><td class="source">  private void drawsegment_plain(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1081

><td class="source">                                 float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1082

><td class="source">                                 int ytop,<br></td></tr
><tr
id=sl_svn7768_1083

><td class="source">                                 int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1084

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1085

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1086

><td class="source">//    int f = m_fill;<br></td></tr
><tr
id=sl_svn7768_1087

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1088

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1089

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1090

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1091

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1092

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1093

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1094

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1095

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1096

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1097

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1098

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1099

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1100

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1101

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1102

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1103

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1104

><td class="source">        if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1105

><td class="source">          m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1106

><td class="source">          m_pixels[xstart] = m_fill;<br></td></tr
><tr
id=sl_svn7768_1107

><td class="source">//          m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1108

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1109

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1110

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1111

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1112

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1113

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1114

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1115

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1116

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1117

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1118

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1119

><td class="source">  <br></td></tr
><tr
id=sl_svn7768_1120

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1121

><td class="source">   * Plain color, interpolated alpha<br></td></tr
><tr
id=sl_svn7768_1122

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1123

><td class="source">  private void drawsegment_plain_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1124

><td class="source">                                       float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1125

><td class="source">                                       int ytop,<br></td></tr
><tr
id=sl_svn7768_1126

><td class="source">                                       int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1127

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1128

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1129

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1130

><td class="source">    int pr = m_fill &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_1131

><td class="source">    int pg = m_fill &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1132

><td class="source">    int pb = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1133

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1134

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1135

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_1136

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1137

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1138

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1139

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1140

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1141

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1142

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1143

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1144

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1145

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1146

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1147

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1148

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_1149

><td class="source">      xstart += ytop;<br></td></tr
><tr
id=sl_svn7768_1150

><td class="source">      xend += ytop;<br></td></tr
><tr
id=sl_svn7768_1151

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1152

><td class="source">      //int ma0 = 0xFF000000;<br></td></tr
><tr
id=sl_svn7768_1153

><td class="source">      <br></td></tr
><tr
id=sl_svn7768_1154

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1155

><td class="source">        if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1156

><td class="source">          // don&#39;t set zbuffer when not fully opaque<br></td></tr
><tr
id=sl_svn7768_1157

><td class="source">          //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1158

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1159

><td class="source">          int alpha = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_1160

><td class="source">          int mr0 = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_1161

><td class="source">          /*<br></td></tr
><tr
id=sl_svn7768_1162

><td class="source">          if (argbSurface) {<br></td></tr
><tr
id=sl_svn7768_1163

><td class="source">            ma0 = (((mr0 &gt;&gt;&gt; 24) * alpha) &lt;&lt; 16) &amp; 0xFF000000;<br></td></tr
><tr
id=sl_svn7768_1164

><td class="source">            if (ma0 == 0) ma0 = alpha &lt;&lt; 24;<br></td></tr
><tr
id=sl_svn7768_1165

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1166

><td class="source">          */<br></td></tr
><tr
id=sl_svn7768_1167

><td class="source">          int mg0 = mr0 &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1168

><td class="source">          int mb0 = mr0 &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1169

><td class="source">          mr0 &amp;= 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_1170

><td class="source">          <br></td></tr
><tr
id=sl_svn7768_1171

><td class="source">          mr0 = mr0 + (((pr - mr0) * alpha) &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn7768_1172

><td class="source">          mg0 = mg0 + (((pg - mg0) * alpha) &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn7768_1173

><td class="source">          mb0 = mb0 + (((pb - mb0) * alpha) &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn7768_1174

><td class="source">          <br></td></tr
><tr
id=sl_svn7768_1175

><td class="source">          m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_1176

><td class="source">            (mr0 &amp; 0xFF0000) | (mg0 &amp; 0xFF00) | (mb0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1177

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1178

><td class="source">//          m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1179

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1180

><td class="source">        iz += izadd;<br></td></tr
><tr
id=sl_svn7768_1181

><td class="source">        ia += iaadd;<br></td></tr
><tr
id=sl_svn7768_1182

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1183

><td class="source">      ytop += SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1184

><td class="source">      xleft += leftadd;<br></td></tr
><tr
id=sl_svn7768_1185

><td class="source">      xrght += rghtadd;<br></td></tr
><tr
id=sl_svn7768_1186

><td class="source">      zleft += zleftadd;<br></td></tr
><tr
id=sl_svn7768_1187

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1188

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1189

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1190

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1191

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1192

><td class="source">   * RGB gouraud<br></td></tr
><tr
id=sl_svn7768_1193

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1194

><td class="source">  private void drawsegment_gouraud(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1195

><td class="source">                                   float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1196

><td class="source">                                   int ytop,<br></td></tr
><tr
id=sl_svn7768_1197

><td class="source">                                   int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1198

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_1199

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_1200

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_1201

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1202

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1203

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1204

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1205

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1206

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1207

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1208

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1209

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1210

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1211

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1212

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1213

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1214

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1215

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1216

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_1217

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_1218

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_1219

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1220

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1221

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1222

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1223

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1224

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1225

><td class="source">        if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1226

><td class="source">          m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1227

><td class="source">          m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_1228

><td class="source">            ((ir &amp; 0xFF0000) | ((ig &gt;&gt; 8) &amp; 0xFF00) | (ib &gt;&gt; 16));<br></td></tr
><tr
id=sl_svn7768_1229

><td class="source">//          m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1230

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1231

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1232

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_1233

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_1234

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_1235

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1236

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1237

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1238

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1239

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1240

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1241

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_1242

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_1243

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_1244

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1245

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1246

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1247

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1248

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1249

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1250

><td class="source">   * RGB gouraud + interpolated alpha<br></td></tr
><tr
id=sl_svn7768_1251

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1252

><td class="source">  private void drawsegment_gouraud_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1253

><td class="source">                                         float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1254

><td class="source">                                         int ytop,<br></td></tr
><tr
id=sl_svn7768_1255

><td class="source">                                         int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1256

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1257

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1258

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1259

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1260

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_1261

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_1262

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_1263

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_1264

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1265

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1266

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1267

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1268

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1269

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1270

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1271

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1272

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1273

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1274

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_1275

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_1276

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_1277

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_1278

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1279

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1280

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1281

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1282

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1283

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1284

><td class="source">        if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1285

><td class="source">          //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1286

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1287

><td class="source">          //<br></td></tr
><tr
id=sl_svn7768_1288

><td class="source">          int red = (ir &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_1289

><td class="source">          int grn = (ig &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1290

><td class="source">          int blu = (ib &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1291

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1292

><td class="source">          // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_1293

><td class="source">          int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_1294

><td class="source">          int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_1295

><td class="source">          int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_1296

><td class="source">          bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_1297

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1298

><td class="source">          // blend alpha<br></td></tr
><tr
id=sl_svn7768_1299

><td class="source">          int al = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_1300

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1301

><td class="source">          //<br></td></tr
><tr
id=sl_svn7768_1302

><td class="source">          m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_1303

><td class="source">            ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) | <br></td></tr
><tr
id=sl_svn7768_1304

><td class="source">            ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_1305

><td class="source">            ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1306

><td class="source">//          m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1307

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1308

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1309

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_1310

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_1311

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_1312

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_1313

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_1314

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1315

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1316

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1317

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1318

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1319

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1320

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_1321

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_1322

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_1323

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_1324

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1325

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1326

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1327

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1328

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1329

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1330

><td class="source">   * 8-bit plain texture<br></td></tr
><tr
id=sl_svn7768_1331

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1332

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1333

><td class="source">   //THIS IS MESSED UP, NEED TO GRAB ORIGINAL VERSION!!!<br></td></tr
><tr
id=sl_svn7768_1334

><td class="source">  private void drawsegment_texture8(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1335

><td class="source">                                    float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1336

><td class="source">                                    int ytop,<br></td></tr
><tr
id=sl_svn7768_1337

><td class="source">                                    int ybottom) {    <br></td></tr
><tr
id=sl_svn7768_1338

><td class="source">    // Accurate texture mode added - comments stripped from dupe code, <br></td></tr
><tr
id=sl_svn7768_1339

><td class="source">    // see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_1340

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_1341

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_1342

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_1343

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_1344

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_1345

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_1346

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1347

><td class="source">    if (accurateMode) {<br></td></tr
><tr
id=sl_svn7768_1348

><td class="source">      // see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_1349

><td class="source">      if (precomputeAccurateTexturing()) { <br></td></tr
><tr
id=sl_svn7768_1350

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1351

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1352

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1353

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_1354

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_1355

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_1356

><td class="source">        // if the matrix inversion screwed up, revert to normal rendering <br></td></tr
><tr
id=sl_svn7768_1357

><td class="source">        // (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_1358

><td class="source">        accurateMode = false; <br></td></tr
><tr
id=sl_svn7768_1359

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1360

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1361

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1362

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1363

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1364

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1365

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_1366

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_1367

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1368

><td class="source">    int red = m_fill &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_1369

><td class="source">    int grn = m_fill &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1370

><td class="source">    int blu = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1371

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1372

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1373

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1374

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1375

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1376

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1377

><td class="source">          int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1378

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1379

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1380

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1381

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1382

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1383

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1384

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_1385

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_1386

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1387

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1388

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1389

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1390

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1391

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1392

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_1393

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_1394

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_1395

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_1396

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_1397

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1398

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_1399

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1400

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_1401

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_1402

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_1403

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1404

><td class="source">      if (accurateMode &amp;&amp; goingIn) {<br></td></tr
><tr
id=sl_svn7768_1405

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1406

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_1407

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1408

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1409

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_1410

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1411

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1412

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1413

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_1414

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1415

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1416

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1417

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1418

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1419

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_1420

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1421

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1422

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU;<br></td></tr
><tr
id=sl_svn7768_1423

><td class="source">        iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_1424

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_1425

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1426

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1427

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1428

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1429

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1430

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1431

><td class="source">        if (accurateMode) {<br></td></tr
><tr
id=sl_svn7768_1432

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1433

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_1434

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_1435

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_1436

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_1437

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1438

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_1439

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1440

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_1441

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1442

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1443

><td class="source">          } else {<br></td></tr
><tr
id=sl_svn7768_1444

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_1445

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_1446

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1447

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_1448

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1449

><td class="source">        // try-catch just in case pixel offset it out of range<br></td></tr
><tr
id=sl_svn7768_1450

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_1451

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1452

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1453

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1454

><td class="source">            int al0;<br></td></tr
><tr
id=sl_svn7768_1455

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_1456

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1457

><td class="source">              int iui = iu &amp; 0xFFFF;<br></td></tr
><tr
id=sl_svn7768_1458

><td class="source">              al0 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1459

><td class="source">              int al1 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1460

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1461

><td class="source">              int al2 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1462

><td class="source">              int al3 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1463

><td class="source">              al0 = al0 + (((al1-al0) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1464

><td class="source">              al2 = al2 + (((al3-al2) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1465

><td class="source">              al0 = al0 + (((al2-al0) * (iv &amp; 0xFFFF)) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1466

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_1467

><td class="source">              al0 = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1468

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_1469

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1470

><td class="source">            int br = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_1471

><td class="source">            int bg = (br &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_1472

><td class="source">            int bb = (br &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1473

><td class="source">            br = (br &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_1474

><td class="source">            m_pixels[xstart] = 0xFF000000 |  <br></td></tr
><tr
id=sl_svn7768_1475

><td class="source">              ((br + (((red - br) * al0) &gt;&gt; 8)) &amp; 0xFF0000) | <br></td></tr
><tr
id=sl_svn7768_1476

><td class="source">              ((bg + (((grn - bg) * al0) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_1477

><td class="source">              ((bb + (((blu - bb) * al0) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1478

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1479

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1480

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1481

><td class="source">        catch (Exception e) {<br></td></tr
><tr
id=sl_svn7768_1482

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1483

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1484

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_1485

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_1486

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_1487

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1488

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1489

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1490

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1491

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1492

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1493

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1494

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_1495

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_1496

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1497

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1498

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1499

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1500

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1501

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1502

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1503

><td class="source">   * 8-bit texutre + alpha<br></td></tr
><tr
id=sl_svn7768_1504

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1505

><td class="source">  private void drawsegment_texture8_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1506

><td class="source">                                          float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1507

><td class="source">                                          int ytop,<br></td></tr
><tr
id=sl_svn7768_1508

><td class="source">                                          int ybottom) {    <br></td></tr
><tr
id=sl_svn7768_1509

><td class="source">    // Accurate texture mode added - comments stripped from dupe code, <br></td></tr
><tr
id=sl_svn7768_1510

><td class="source">    // see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_1511

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_1512

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_1513

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_1514

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_1515

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_1516

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_1517

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_1518

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1519

><td class="source">    if (accurateMode) {<br></td></tr
><tr
id=sl_svn7768_1520

><td class="source">      // see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_1521

><td class="source">      if (precomputeAccurateTexturing()) { <br></td></tr
><tr
id=sl_svn7768_1522

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1523

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1524

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1525

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_1526

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_1527

><td class="source">      } else {<br></td></tr
><tr
id=sl_svn7768_1528

><td class="source">        // if the matrix inversion screwed up, <br></td></tr
><tr
id=sl_svn7768_1529

><td class="source">        // revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_1530

><td class="source">        accurateMode = false; <br></td></tr
><tr
id=sl_svn7768_1531

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1532

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1533

><td class="source">    ytop*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1534

><td class="source">    ybottom*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1535

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1536

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1537

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_1538

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_1539

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_1540

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1541

><td class="source">    int red = m_fill &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_1542

><td class="source">    int grn = m_fill &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1543

><td class="source">    int blu = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1544

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1545

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1546

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1547

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1548

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1549

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1550

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1551

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1552

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1553

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1554

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1555

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1556

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1557

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_1558

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_1559

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_1560

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1561

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1562

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1563

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1564

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1565

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1566

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_1567

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_1568

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_1569

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_1570

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_1571

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1572

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_1573

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1574

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_1575

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_1576

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_1577

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1578

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_1579

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1580

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_1581

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1582

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1583

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_1584

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1585

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1586

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1587

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_1588

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1589

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1590

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1591

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1592

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1593

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_1594

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1595

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1596

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_1597

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_1598

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1599

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1600

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1601

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1602

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1603

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1604

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_1605

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_1606

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1607

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_1608

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_1609

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_1610

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_1611

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1612

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_1613

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1614

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_1615

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1616

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1617

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_1618

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_1619

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_1620

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1621

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_1622

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1623

><td class="source">        // try-catch just in case pixel offset it out of range<br></td></tr
><tr
id=sl_svn7768_1624

><td class="source">        try<br></td></tr
><tr
id=sl_svn7768_1625

><td class="source">          {<br></td></tr
><tr
id=sl_svn7768_1626

><td class="source">            if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1627

><td class="source">              //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1628

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1629

><td class="source">              int al0;<br></td></tr
><tr
id=sl_svn7768_1630

><td class="source">              if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_1631

><td class="source">                int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1632

><td class="source">                int iui = iu &amp; 0xFFFF;<br></td></tr
><tr
id=sl_svn7768_1633

><td class="source">                al0 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1634

><td class="source">                int al1 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1635

><td class="source">                if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1636

><td class="source">                int al2 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1637

><td class="source">                int al3 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1638

><td class="source">                al0 = al0 + (((al1-al0) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1639

><td class="source">                al2 = al2 + (((al3-al2) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1640

><td class="source">                al0 = al0 + (((al2-al0) * (iv &amp; 0xFFFF)) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1641

><td class="source">              } else {<br></td></tr
><tr
id=sl_svn7768_1642

><td class="source">                al0 = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1643

><td class="source">              }<br></td></tr
><tr
id=sl_svn7768_1644

><td class="source">              al0 = (al0 * (ia &gt;&gt; 16)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_1645

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1646

><td class="source">              int br = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_1647

><td class="source">              int bg = (br &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_1648

><td class="source">              int bb = (br &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1649

><td class="source">              br = (br &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_1650

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_1651

><td class="source">                ((br + (((red - br) * al0) &gt;&gt; 8)) &amp; 0xFF0000) | <br></td></tr
><tr
id=sl_svn7768_1652

><td class="source">                ((bg + (((grn - bg) * al0) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_1653

><td class="source">                ((bb + (((blu - bb) * al0) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1654

><td class="source">//              m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1655

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_1656

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1657

><td class="source">        catch (Exception e) {<br></td></tr
><tr
id=sl_svn7768_1658

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1659

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1660

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_1661

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_1662

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_1663

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1664

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1665

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_1666

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1667

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1668

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1669

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1670

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1671

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_1672

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_1673

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1674

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_1675

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1676

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1677

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1678

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1679

><td class="source">   * Plain 24-bit texture<br></td></tr
><tr
id=sl_svn7768_1680

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1681

><td class="source">  private void drawsegment_texture24(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1682

><td class="source">                                     float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1683

><td class="source">                                     int ytop,<br></td></tr
><tr
id=sl_svn7768_1684

><td class="source">                                     int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1685

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1686

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1687

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1688

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_1689

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_1690

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_1691

><td class="source">    boolean tint = (m_fill &amp; 0xFFFFFF) != 0xFFFFFF;<br></td></tr
><tr
id=sl_svn7768_1692

><td class="source">    int rtint = (m_fill &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_1693

><td class="source">    int gtint = (m_fill &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_1694

><td class="source">    int btint = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1695

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1696

><td class="source">    int ypixel = ytop/SCREEN_WIDTH;//ACCTEX<br></td></tr
><tr
id=sl_svn7768_1697

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;//If we&#39;re past this index, we can&#39;t shift down a row w/o throwing an exception<br></td></tr
><tr
id=sl_svn7768_1698

><td class="source">    //      int exCount = 0;//counter for exceptions caught<br></td></tr
><tr
id=sl_svn7768_1699

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES]; //bring this local since it will be accessed often<br></td></tr
><tr
id=sl_svn7768_1700

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_1701

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_1702

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1703

><td class="source">    //Interpolation length of 16 tends to look good except at a small angle; 8 looks okay then, except for the<br></td></tr
><tr
id=sl_svn7768_1704

><td class="source">    //above issue.  When viewing close to flat, as high as 32 is often acceptable.  Could add dynamic interpolation<br></td></tr
><tr
id=sl_svn7768_1705

><td class="source">    //settings based on triangle angle - currently we just pick a value and leave it (by default I have the<br></td></tr
><tr
id=sl_svn7768_1706

><td class="source">    //power set at 3, so every 8 pixels a true coordinate is calculated, which seems a decent compromise).<br></td></tr
><tr
id=sl_svn7768_1707

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1708

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_1709

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1710

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1711

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_1712

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1713

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1714

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1715

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_1716

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_1717

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_1718

><td class="source">        accurateMode = false; //if the matrix inversion gave us garbage, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_1719

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1720

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1721

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1722

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1723

><td class="source">    while (ytop &lt; ybottom) {//scanline loop<br></td></tr
><tr
id=sl_svn7768_1724

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1725

><td class="source">      if (xstart &lt; 0){ xstart = 0; }<br></td></tr
><tr
id=sl_svn7768_1726

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1727

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1728

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1729

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1730

><td class="source">      if (xend &gt; SCREEN_WIDTH){ xend = SCREEN_WIDTH; }<br></td></tr
><tr
id=sl_svn7768_1731

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1732

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_1733

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_1734

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1735

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1736

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1737

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1738

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1739

><td class="source">        //off by one (half, I guess) hack, w/o it the first rows are outside the texture - maybe a mistake somewhere?<br></td></tr
><tr
id=sl_svn7768_1740

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_1741

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_1742

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;//OPT - some of this could be brought out of the y-loop since<br></td></tr
><tr
id=sl_svn7768_1743

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;//xpixel and ypixel just increment by the same numbers each iteration.<br></td></tr
><tr
id=sl_svn7768_1744

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;//Probably not a big bottleneck, though.<br></td></tr
><tr
id=sl_svn7768_1745

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1746

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1747

><td class="source">      //Figure out whether triangle is going further into the screen or not as we move along scanline<br></td></tr
><tr
id=sl_svn7768_1748

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_1749

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1750

><td class="source">      //Set up linear interpolation between calculated texture points<br></td></tr
><tr
id=sl_svn7768_1751

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1752

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_1753

><td class="source">      //float fdeltaU = 0; float fdeltaV = 0;//vars for floating point interpolating version of algorithm<br></td></tr
><tr
id=sl_svn7768_1754

><td class="source">      //float fiu = 0; float fiv = 0;<br></td></tr
><tr
id=sl_svn7768_1755

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_1756

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_1757

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1758

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1759

><td class="source">      //Bugfix (done): it&#39;s a Really Bad Thing to interpolate along a scanline when the triangle goes deeper into the screen,<br></td></tr
><tr
id=sl_svn7768_1760

><td class="source">      //because if the angle is severe enough the last control point for interpolation may cross the vanishing<br></td></tr
><tr
id=sl_svn7768_1761

><td class="source">      //point.  This leads to some pretty nasty artifacts, and ideally we should scan from right to left if the<br></td></tr
><tr
id=sl_svn7768_1762

><td class="source">      //triangle is better served that way, or (what we do now) precompute the offset that we&#39;ll need so that we end up<br></td></tr
><tr
id=sl_svn7768_1763

><td class="source">      //with a control point exactly at the furthest edge of the triangle.<br></td></tr
><tr
id=sl_svn7768_1764

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1765

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_1766

><td class="source">        //IMPORTANT!!!  Results are horrid without this hack!<br></td></tr
><tr
id=sl_svn7768_1767

><td class="source">        //If polygon goes into the screen along scan line, we want to match the control point to the furthest point drawn<br></td></tr
><tr
id=sl_svn7768_1768

><td class="source">        //since the control points are less meaningful the closer you are to the vanishing point.<br></td></tr
><tr
id=sl_svn7768_1769

><td class="source">        //We&#39;ll do this by making the first control point lie before the start of the scanline (safe since it&#39;s closer to us)<br></td></tr
><tr
id=sl_svn7768_1770

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1771

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength; //&quot;off by one&quot; hack...probably means there&#39;s a small bug somewhere<br></td></tr
><tr
id=sl_svn7768_1772

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_1773

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1774

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_1775

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_1776

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1777

><td class="source">        //Take step to control point to the left of start pixel<br></td></tr
><tr
id=sl_svn7768_1778

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1779

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1780

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1781

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_1782

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1783

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1784

><td class="source">        //Now step to right control point<br></td></tr
><tr
id=sl_svn7768_1785

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_1786

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_1787

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_1788

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1789

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_1790

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1791

><td class="source">        //Get deltas for interpolation<br></td></tr
><tr
id=sl_svn7768_1792

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1793

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1794

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_1795

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_1796

><td class="source">        //Otherwise the left edge is further, and we pin the first control point to it<br></td></tr
><tr
id=sl_svn7768_1797

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1798

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1799

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_1800

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1801

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1802

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {//pixel loop - keep trim, can execute thousands of times per frame<br></td></tr
><tr
id=sl_svn7768_1803

><td class="source">        //boolean drawBlack = false; //used to display control points<br></td></tr
><tr
id=sl_svn7768_1804

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_1805

><td class="source">          /*  //Non-interpolating algorithm - slowest version, calculates exact coordinate for each pixel,<br></td></tr
><tr
id=sl_svn7768_1806

><td class="source">          //and casts from float-&gt;int<br></td></tr
><tr
id=sl_svn7768_1807

><td class="source">          float oneoverc = 65536.0f/c;  //a bit faster to pre-divide for next two steps<br></td></tr
><tr
id=sl_svn7768_1808

><td class="source">          iu = (int)(a*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1809

><td class="source">          iv = (int)(b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1810

><td class="source">          a += newax;<br></td></tr
><tr
id=sl_svn7768_1811

><td class="source">          b += newbx;<br></td></tr
><tr
id=sl_svn7768_1812

><td class="source">          c += newcx;<br></td></tr
><tr
id=sl_svn7768_1813

><td class="source">          */<br></td></tr
><tr
id=sl_svn7768_1814

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1815

><td class="source">          //Float while calculating, int while interpolating<br></td></tr
><tr
id=sl_svn7768_1816

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_1817

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_1818

><td class="source">            //drawBlack = true;<br></td></tr
><tr
id=sl_svn7768_1819

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_1820

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_1821

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_1822

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1823

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_1824

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1825

><td class="source">            iu = (int)oldfu; iv = (int)oldfv; //ints are used for interpolation, not actual computation<br></td></tr
><tr
id=sl_svn7768_1826

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1827

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1828

><td class="source">          } else{        //race through using linear interpolation if we&#39;re not at a control point<br></td></tr
><tr
id=sl_svn7768_1829

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_1830

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_1831

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1832

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_1833

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1834

><td class="source">          /* //Floating point interpolating version - slower than int thanks to casts during interpolation steps<br></td></tr
><tr
id=sl_svn7768_1835

><td class="source">             if (interpCounter == 0) {<br></td></tr
><tr
id=sl_svn7768_1836

><td class="source">             interpCounter = linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1837

><td class="source">             a += newax;<br></td></tr
><tr
id=sl_svn7768_1838

><td class="source">             b += newbx;<br></td></tr
><tr
id=sl_svn7768_1839

><td class="source">             c += newcx;<br></td></tr
><tr
id=sl_svn7768_1840

><td class="source">             float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_1841

><td class="source">             oldfu = fu;<br></td></tr
><tr
id=sl_svn7768_1842

><td class="source">             oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_1843

><td class="source">             fu = (a*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1844

><td class="source">             fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_1845

><td class="source">             //oldu = u; oldv = v;<br></td></tr
><tr
id=sl_svn7768_1846

><td class="source">             fiu = oldfu;<br></td></tr
><tr
id=sl_svn7768_1847

><td class="source">             fiv = oldfv;<br></td></tr
><tr
id=sl_svn7768_1848

><td class="source">             fdeltaU = (fu-oldfu)/linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1849

><td class="source">             fdeltaV = (fv-oldfv)/linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1850

><td class="source">             }<br></td></tr
><tr
id=sl_svn7768_1851

><td class="source">             else{<br></td></tr
><tr
id=sl_svn7768_1852

><td class="source">             fiu += fdeltaU;<br></td></tr
><tr
id=sl_svn7768_1853

><td class="source">             fiv += fdeltaV;<br></td></tr
><tr
id=sl_svn7768_1854

><td class="source">             }<br></td></tr
><tr
id=sl_svn7768_1855

><td class="source">             interpCounter--;<br></td></tr
><tr
id=sl_svn7768_1856

><td class="source">             iu = (int)(fiu); iv = (int)(fiv);*/<br></td></tr
><tr
id=sl_svn7768_1857

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1858

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1859

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1860

><td class="source">        // try-catch just in case pixel offset is out of range<br></td></tr
><tr
id=sl_svn7768_1861

><td class="source">        try{<br></td></tr
><tr
id=sl_svn7768_1862

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_1863

><td class="source">            m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_1864

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_1865

><td class="source">              //We could (should?) add bounds checking on iu and iv here (keep in mind the 16 bit shift!).<br></td></tr
><tr
id=sl_svn7768_1866

><td class="source">              //This would also be the place to add looping texture mode (bounds check == clamped).<br></td></tr
><tr
id=sl_svn7768_1867

><td class="source">              //For looping/clamped textures, we&#39;d also need to change PGraphics.textureVertex() to remove<br></td></tr
><tr
id=sl_svn7768_1868

><td class="source">              //the texture range check there (it constrains normalized texture coordinates from 0-&gt;1).<br></td></tr
><tr
id=sl_svn7768_1869

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1870

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_1871

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_1872

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_1873

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1874

><td class="source">              //if(ofs &lt; 0) { ofs += TEX_WIDTH; }<br></td></tr
><tr
id=sl_svn7768_1875

><td class="source">              //if(ofs &gt; m_texture.length-2) {ofs -= TEX_WIDTH; }<br></td></tr
><tr
id=sl_svn7768_1876

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1877

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_1878

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_1879

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_1880

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH; //quick hack to thwart exceptions<br></td></tr
><tr
id=sl_svn7768_1881

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_1882

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_1883

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1884

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_1885

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_1886

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_1887

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1888

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1889

><td class="source">              int red = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1890

><td class="source">              if (tint) red = ((red * rtint) &gt;&gt; 8) &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_1891

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1892

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_1893

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_1894

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_1895

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1896

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1897

><td class="source">              int grn = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1898

><td class="source">              if (tint) grn = ((grn * gtint) &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_1899

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1900

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_1901

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1902

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1903

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1904

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1905

><td class="source">              int blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_1906

><td class="source">              if (tint) blu = ((blu * btint) &gt;&gt; 8) &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1907

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1908

><td class="source">              //m_pixels[xstart] = (red &amp; 0xFF0000) | (grn &amp; 0xFF00) | (blu &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1909

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_1910

><td class="source">                (red &amp; 0xFF0000) | (grn &amp; 0xFF00) | (blu &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_1911

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1912

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_1913

><td class="source">              m_pixels[xstart] = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_1914

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_1915

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_1916

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_1917

><td class="source">        } catch (Exception e) {/*exCount++;*/}<br></td></tr
><tr
id=sl_svn7768_1918

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_1919

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1920

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_1921

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_1922

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_1923

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_1924

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1925

><td class="source">      ypixel++; //accurate mode<br></td></tr
><tr
id=sl_svn7768_1926

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1927

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_1928

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_1929

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_1930

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_1931

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_1932

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1933

><td class="source">    //if (exCount&gt;0) System.out.println(exCount+&quot; exceptions in this segment&quot;);<br></td></tr
><tr
id=sl_svn7768_1934

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_1935

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1936

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1937

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_1938

><td class="source">   * Alpha 24-bit texture<br></td></tr
><tr
id=sl_svn7768_1939

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_1940

><td class="source">  private void drawsegment_texture24_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_1941

><td class="source">                                           float rghtadd,<br></td></tr
><tr
id=sl_svn7768_1942

><td class="source">                                           int ytop,<br></td></tr
><tr
id=sl_svn7768_1943

><td class="source">                                           int ybottom) {<br></td></tr
><tr
id=sl_svn7768_1944

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_1945

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_1946

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_1947

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_1948

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_1949

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_1950

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_1951

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_1952

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1953

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_1954

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1955

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1956

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_1957

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_1958

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_1959

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_1960

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_1961

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_1962

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_1963

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1964

><td class="source">    boolean tint = (m_fill &amp; 0xFFFFFF) != 0xFFFFFF;<br></td></tr
><tr
id=sl_svn7768_1965

><td class="source">    int rtint = (m_fill &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_1966

><td class="source">    int gtint = (m_fill &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_1967

><td class="source">    int btint = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_1968

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_1969

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1970

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1971

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_1972

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1973

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_1974

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_1975

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_1976

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1977

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_1978

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1979

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_1980

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_1981

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1982

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_1983

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1984

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_1985

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_1986

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_1987

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1988

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_1989

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_1990

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_1991

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_1992

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_1993

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1994

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_1995

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_1996

><td class="source"><br></td></tr
><tr
id=sl_svn7768_1997

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_1998

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_1999

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_2000

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_2001

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_2002

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_2003

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2004

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_2005

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2006

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_2007

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_2008

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_2009

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2010

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_2011

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2012

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_2013

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2014

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2015

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_2016

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2017

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2018

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2019

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_2020

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2021

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2022

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2023

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2024

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2025

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_2026

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2027

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2028

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_2029

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2030

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2031

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2032

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2033

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2034

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2035

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2036

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_2037

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_2038

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2039

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_2040

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_2041

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_2042

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_2043

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2044

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_2045

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2046

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_2047

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2048

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2049

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_2050

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_2051

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_2052

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2053

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_2054

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2055

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2056

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_2057

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_2058

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_2059

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2060

><td class="source">            // get alpha<br></td></tr
><tr
id=sl_svn7768_2061

><td class="source">            int al = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_2062

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2063

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_2064

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2065

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2066

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2067

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2068

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_2069

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2070

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2071

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2072

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2073

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2074

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2075

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_2076

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2077

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2078

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2079

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2080

><td class="source">              int red = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2081

><td class="source">              if (tint) red = ((red * rtint) &gt;&gt; 8) &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2082

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2083

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_2084

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2085

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2086

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2087

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2088

><td class="source">              int grn = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2089

><td class="source">              if (tint) grn = ((grn * gtint) &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2090

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2091

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_2092

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2093

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2094

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2095

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2096

><td class="source">              int blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2097

><td class="source">              if (tint) blu = ((blu * btint) &gt;&gt; 8) &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2098

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2099

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2100

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2101

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2102

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2103

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2104

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2105

><td class="source">                ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2106

><td class="source">                ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2107

><td class="source">                ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2108

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2109

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_2110

><td class="source">              int red = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_2111

><td class="source">              int grn = red &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2112

><td class="source">              int blu = red &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2113

><td class="source">              red&amp;=0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2114

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2115

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2116

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2117

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2118

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2119

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2120

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2121

><td class="source">                ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2122

><td class="source">                ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) |<br></td></tr
><tr
id=sl_svn7768_2123

><td class="source">                ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2124

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_2125

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_2126

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2127

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_2128

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_2129

><td class="source">        xpixel++; // accurate mode<br></td></tr
><tr
id=sl_svn7768_2130

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_2131

><td class="source">          iu += iuadd;<br></td></tr
><tr
id=sl_svn7768_2132

><td class="source">          iv += ivadd;<br></td></tr
><tr
id=sl_svn7768_2133

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2134

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_2135

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_2136

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2137

><td class="source">      ypixel++; // accurate mode<br></td></tr
><tr
id=sl_svn7768_2138

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2139

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2140

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2141

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_2142

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_2143

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_2144

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_2145

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_2146

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_2147

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2148

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_2149

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2150

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_2151

><td class="source">   * Plain 32-bit texutre<br></td></tr
><tr
id=sl_svn7768_2152

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_2153

><td class="source">  private void drawsegment_texture32(float leftadd,<br></td></tr
><tr
id=sl_svn7768_2154

><td class="source">                                     float rghtadd,<br></td></tr
><tr
id=sl_svn7768_2155

><td class="source">                                     int ytop,<br></td></tr
><tr
id=sl_svn7768_2156

><td class="source">                                     int ybottom) {<br></td></tr
><tr
id=sl_svn7768_2157

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_2158

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_2159

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_2160

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_2161

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_2162

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_2163

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_2164

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2165

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2166

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_2167

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2168

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2169

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2170

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_2171

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_2172

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2173

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_2174

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2175

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2176

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2177

><td class="source">    ytop*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2178

><td class="source">    ybottom*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2179

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_2180

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2181

><td class="source">    boolean tint = m_fill != 0xFFFFFFFF;<br></td></tr
><tr
id=sl_svn7768_2182

><td class="source">    int rtint = (m_fill &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_2183

><td class="source">    int gtint = (m_fill &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_2184

><td class="source">    int btint = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2185

><td class="source">    <br></td></tr
><tr
id=sl_svn7768_2186

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_2187

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_2188

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2189

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_2190

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2191

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_2192

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_2193

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2194

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2195

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2196

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2197

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_2198

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2199

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2200

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_2201

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_2202

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_2203

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_2204

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2205

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_2206

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_2207

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2208

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2209

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_2210

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_2211

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_2212

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_2213

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_2214

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2215

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_2216

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2217

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_2218

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_2219

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_2220

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2221

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_2222

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2223

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_2224

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2225

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2226

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_2227

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2228

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2229

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2230

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_2231

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2232

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2233

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2234

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2235

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2236

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_2237

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2238

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2239

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_2240

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2241

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2242

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2243

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2244

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2245

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2246

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2247

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_2248

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_2249

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2250

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_2251

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_2252

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_2253

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_2254

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2255

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_2256

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2257

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_2258

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2259

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2260

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_2261

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_2262

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_2263

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2264

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_2265

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2266

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2267

><td class="source">        // try-catch just in case pixel offset it out of range<br></td></tr
><tr
id=sl_svn7768_2268

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_2269

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_2270

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_2271

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2272

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_2273

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2274

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2275

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2276

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2277

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_2278

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2279

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2280

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2281

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2282

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2283

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2284

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_2285

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2286

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2287

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2288

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2289

><td class="source">              int red = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2290

><td class="source">              if (tint) red = ((red * rtint) &gt;&gt; 8) &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2291

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2292

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_2293

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2294

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2295

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2296

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2297

><td class="source">              int grn = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2298

><td class="source">              if (tint) grn = ((grn * gtint) &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2299

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2300

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_2301

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2302

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2303

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2304

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2305

><td class="source">              int blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2306

><td class="source">              if (tint) blu = ((blu * btint) &gt;&gt; 8) &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2307

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2308

><td class="source">              // alpha<br></td></tr
><tr
id=sl_svn7768_2309

><td class="source">              pix0&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_2310

><td class="source">              pix2&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_2311

><td class="source">              up = pix0 + ((((pix1 &gt;&gt;&gt; 24) - pix0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2312

><td class="source">              dn = pix2 + ((((pix3 &gt;&gt;&gt; 24) - pix2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2313

><td class="source">              int al = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2314

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2315

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2316

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2317

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2318

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2319

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2320

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2321

><td class="source">                ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2322

><td class="source">                ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2323

><td class="source">                ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2324

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_2325

><td class="source">              int red = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_2326

><td class="source">              int al = red &gt;&gt;&gt; 24;<br></td></tr
><tr
id=sl_svn7768_2327

><td class="source">              int grn = red &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2328

><td class="source">              int blu = red &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2329

><td class="source">              red&amp;=0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2330

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2331

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2332

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2333

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2334

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2335

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2336

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2337

><td class="source">              ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2338

><td class="source">              ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2339

><td class="source">              ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2340

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_2341

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_2342

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2343

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_2344

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2345

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_2346

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_2347

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_2348

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2349

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_2350

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2351

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2352

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2353

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2354

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2355

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_2356

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_2357

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_2358

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_2359

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_2360

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_2361

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2362

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2363

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2364

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_2365

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2366

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_2367

><td class="source">   * Alpha 32-bit texutre<br></td></tr
><tr
id=sl_svn7768_2368

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_2369

><td class="source">  private void drawsegment_texture32_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_2370

><td class="source">                                           float rghtadd,<br></td></tr
><tr
id=sl_svn7768_2371

><td class="source">                                           int ytop,<br></td></tr
><tr
id=sl_svn7768_2372

><td class="source">                                           int ybottom) {<br></td></tr
><tr
id=sl_svn7768_2373

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_2374

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_2375

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_2376

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_2377

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_2378

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_2379

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_2380

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2381

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2382

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_2383

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2384

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2385

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2386

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_2387

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_2388

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2389

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_2390

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2391

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2392

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2393

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2394

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2395

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_2396

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2397

><td class="source">    boolean tint = (m_fill &amp; 0xFFFFFF) != 0xFFFFFF;<br></td></tr
><tr
id=sl_svn7768_2398

><td class="source">    int rtint = (m_fill &gt;&gt; 16) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_2399

><td class="source">    int gtint = (m_fill &gt;&gt; 8) &amp; 0xff;<br></td></tr
><tr
id=sl_svn7768_2400

><td class="source">    int btint = m_fill &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2401

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2402

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_2403

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_2404

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_2405

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2406

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_2407

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2408

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_2409

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_2410

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2411

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2412

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2413

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2414

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_2415

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2416

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2417

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_2418

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_2419

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_2420

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_2421

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_2422

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2423

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_2424

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_2425

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2426

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2427

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_2428

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_2429

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_2430

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_2431

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_2432

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2433

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_2434

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2435

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_2436

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_2437

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_2438

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2439

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_2440

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2441

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_2442

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2443

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2444

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_2445

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2446

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2447

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2448

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_2449

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2450

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2451

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2452

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2453

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2454

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_2455

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2456

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2457

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_2458

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2459

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2460

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2461

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2462

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2463

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2464

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_2465

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_2466

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2467

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_2468

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_2469

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_2470

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_2471

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2472

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_2473

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2474

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_2475

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2476

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2477

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_2478

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_2479

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_2480

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2481

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_2482

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2483

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2484

><td class="source">        // try-catch just in case pixel offset it out of range<br></td></tr
><tr
id=sl_svn7768_2485

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_2486

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_2487

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_2488

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2489

><td class="source">            // get alpha<br></td></tr
><tr
id=sl_svn7768_2490

><td class="source">            int al = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_2491

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2492

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_2493

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2494

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2495

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_2496

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2497

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_2498

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2499

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2500

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2501

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_2502

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_2503

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2504

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_2505

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2506

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_2507

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2508

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2509

><td class="source">              int red = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2510

><td class="source">              if (tint) red = ((red * rtint) &gt;&gt; 8) &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2511

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2512

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_2513

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2514

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_2515

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2516

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2517

><td class="source">              int grn = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2518

><td class="source">              if (tint) grn = ((grn * gtint) &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2519

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2520

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_2521

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2522

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2523

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2524

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2525

><td class="source">              int blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2526

><td class="source">              if (tint) blu = ((blu * btint) &gt;&gt; 8) &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2527

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2528

><td class="source">              // alpha<br></td></tr
><tr
id=sl_svn7768_2529

><td class="source">              pix0&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_2530

><td class="source">              pix2&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_2531

><td class="source">              up = pix0 + ((((pix1 &gt;&gt;&gt; 24) - pix0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2532

><td class="source">              dn = pix2 + ((((pix3 &gt;&gt;&gt; 24) - pix2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_2533

><td class="source">              al = al * (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_2534

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2535

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2536

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2537

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2538

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2539

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2540

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2541

><td class="source">              ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2542

><td class="source">              ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2543

><td class="source">              ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2544

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_2545

><td class="source">              int red = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_2546

><td class="source">              al = al * (red &gt;&gt;&gt; 24) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_2547

><td class="source">              int grn = red &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2548

><td class="source">              int blu = red &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2549

><td class="source">              red&amp;=0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2550

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2551

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2552

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2553

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2554

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2555

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2556

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_2557

><td class="source">              ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2558

><td class="source">              ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2559

><td class="source">              ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2560

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_2561

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_2562

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2563

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_2564

><td class="source">        <br></td></tr
><tr
id=sl_svn7768_2565

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2566

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_2567

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_2568

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_2569

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2570

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_2571

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_2572

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2573

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2574

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2575

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2576

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2577

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_2578

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_2579

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_2580

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_2581

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_2582

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_2583

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2584

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2585

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2586

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_2587

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2588

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2589

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_2590

><td class="source">   * Gouraud blended with 8-bit alpha texture<br></td></tr
><tr
id=sl_svn7768_2591

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_2592

><td class="source">  private void drawsegment_gouraud_texture8(float leftadd,<br></td></tr
><tr
id=sl_svn7768_2593

><td class="source">                                            float rghtadd,<br></td></tr
><tr
id=sl_svn7768_2594

><td class="source">                                            int ytop,<br></td></tr
><tr
id=sl_svn7768_2595

><td class="source">                                            int ybottom) {<br></td></tr
><tr
id=sl_svn7768_2596

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_2597

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_2598

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_2599

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_2600

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_2601

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_2602

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_2603

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2604

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2605

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_2606

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2607

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2608

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2609

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_2610

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_2611

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2612

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_2613

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2614

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2615

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2616

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2617

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2618

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_2619

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2620

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_2621

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_2622

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_2623

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_2624

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_2625

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2626

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_2627

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2628

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_2629

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_2630

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2631

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2632

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2633

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2634

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_2635

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2636

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_2637

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2638

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_2639

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_2640

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_2641

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_2642

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_2643

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_2644

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2645

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_2646

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_2647

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2648

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2649

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_2650

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_2651

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_2652

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_2653

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_2654

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2655

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_2656

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2657

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_2658

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_2659

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_2660

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2661

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_2662

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2663

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_2664

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2665

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2666

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_2667

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2668

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2669

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2670

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_2671

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2672

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2673

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2674

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2675

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2676

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_2677

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2678

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2679

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_2680

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2681

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2682

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2683

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2684

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2685

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2686

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2687

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_2688

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_2689

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2690

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_2691

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_2692

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_2693

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_2694

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2695

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_2696

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2697

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_2698

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2699

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2700

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_2701

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_2702

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_2703

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2704

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_2705

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2706

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2707

><td class="source">        try<br></td></tr
><tr
id=sl_svn7768_2708

><td class="source">          {<br></td></tr
><tr
id=sl_svn7768_2709

><td class="source">            if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_2710

><td class="source">              //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_2711

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2712

><td class="source">              int al0;<br></td></tr
><tr
id=sl_svn7768_2713

><td class="source">              if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_2714

><td class="source">                int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2715

><td class="source">                int iui = iu &amp; 0xFFFF;<br></td></tr
><tr
id=sl_svn7768_2716

><td class="source">                al0 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2717

><td class="source">                int al1 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2718

><td class="source">                if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2719

><td class="source">                int al2 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2720

><td class="source">                int al3 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2721

><td class="source">                al0 = al0 + (((al1-al0) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2722

><td class="source">                al2 = al2 + (((al3-al2) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2723

><td class="source">                al0 = al0 + (((al2-al0) * (iv &amp; 0xFFFF)) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2724

><td class="source">              } else {<br></td></tr
><tr
id=sl_svn7768_2725

><td class="source">                al0 = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2726

><td class="source">              }<br></td></tr
><tr
id=sl_svn7768_2727

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2728

><td class="source">              // get RGB colors<br></td></tr
><tr
id=sl_svn7768_2729

><td class="source">              int red = ir &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2730

><td class="source">              int grn = (ig &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2731

><td class="source">              int blu = (ib &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2732

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2733

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2734

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2735

><td class="source">              int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2736

><td class="source">              int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2737

><td class="source">              bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2738

><td class="source">              m_pixels[xstart] = 0xFF000000 |<br></td></tr
><tr
id=sl_svn7768_2739

><td class="source">                ((br + (((red - br) * al0) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2740

><td class="source">                ((bg + (((grn - bg) * al0) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2741

><td class="source">                ((bb + (((blu - bb) * al0) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2742

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2743

><td class="source">              // write stencil<br></td></tr
><tr
id=sl_svn7768_2744

><td class="source">//              m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_2745

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_2746

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2747

><td class="source">        catch (Exception e) {<br></td></tr
><tr
id=sl_svn7768_2748

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2749

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2750

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2751

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_2752

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2753

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_2754

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_2755

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_2756

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2757

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_2758

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_2759

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_2760

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_2761

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2762

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2763

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2764

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_2765

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_2766

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2767

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_2768

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_2769

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_2770

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_2771

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_2772

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_2773

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2774

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_2775

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2776

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2777

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_2778

><td class="source">   * Texture multiplied with gouraud<br></td></tr
><tr
id=sl_svn7768_2779

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_2780

><td class="source">  private void drawsegment_gouraud_texture8_alpha(float leftadd,<br></td></tr
><tr
id=sl_svn7768_2781

><td class="source">                                                  float rghtadd,<br></td></tr
><tr
id=sl_svn7768_2782

><td class="source">                                                  int ytop,<br></td></tr
><tr
id=sl_svn7768_2783

><td class="source">                                                  int ybottom) {<br></td></tr
><tr
id=sl_svn7768_2784

><td class="source">    // Accurate texture mode added - comments stripped from dupe code, <br></td></tr
><tr
id=sl_svn7768_2785

><td class="source">    // see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_2786

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_2787

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_2788

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_2789

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_2790

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_2791

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_2792

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2793

><td class="source">    if (accurateMode) {<br></td></tr
><tr
id=sl_svn7768_2794

><td class="source">      // see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_2795

><td class="source">      if (precomputeAccurateTexturing()) { <br></td></tr
><tr
id=sl_svn7768_2796

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2797

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2798

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2799

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_2800

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_2801

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2802

><td class="source">        // if the matrix inversion screwed up, <br></td></tr
><tr
id=sl_svn7768_2803

><td class="source">        // revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_2804

><td class="source">        accurateMode = false; <br></td></tr
><tr
id=sl_svn7768_2805

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2806

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2807

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2808

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2809

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2810

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_2811

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2812

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_2813

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_2814

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_2815

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_2816

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_2817

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_2818

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2819

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_2820

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2821

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_2822

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_2823

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2824

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2825

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2826

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_2827

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_2828

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2829

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_2830

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2831

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_2832

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_2833

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_2834

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_2835

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_2836

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_2837

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_2838

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2839

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_2840

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_2841

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2842

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2843

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_2844

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_2845

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_2846

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_2847

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_2848

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2849

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_2850

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2851

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_2852

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_2853

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_2854

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2855

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_2856

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2857

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_2858

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2859

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_2860

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_2861

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2862

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2863

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2864

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_2865

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2866

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_2867

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_2868

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_2869

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2870

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_2871

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2872

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2873

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_2874

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2875

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2876

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2877

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_2878

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2879

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2880

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2881

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_2882

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_2883

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_2884

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_2885

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_2886

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_2887

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_2888

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_2889

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_2890

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_2891

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_2892

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2893

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2894

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_2895

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_2896

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_2897

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2898

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_2899

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2900

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2901

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_2902

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_2903

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_2904

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2905

><td class="source">            int al0;<br></td></tr
><tr
id=sl_svn7768_2906

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_2907

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2908

><td class="source">              int iui = iu &amp; 0xFFFF;<br></td></tr
><tr
id=sl_svn7768_2909

><td class="source">              al0 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2910

><td class="source">              int al1 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2911

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2912

><td class="source">              int al2 = m_texture[ofs] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2913

><td class="source">              int al3 = m_texture[ofs + 1] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2914

><td class="source">              al0 = al0 + (((al1-al0) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2915

><td class="source">              al2 = al2 + (((al3-al2) * iui) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2916

><td class="source">              al0 = al0 + (((al2-al0) * (iv &amp; 0xFFFF)) &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2917

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_2918

><td class="source">              al0 = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)] &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_2919

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_2920

><td class="source">            al0 = (al0 * (ia &gt;&gt; 16)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_2921

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2922

><td class="source">            // get RGB colors<br></td></tr
><tr
id=sl_svn7768_2923

><td class="source">            int red = ir &amp; 0xFF0000;<br></td></tr
><tr
id=sl_svn7768_2924

><td class="source">            int grn = (ig &gt;&gt; 8) &amp; 0xFF00;<br></td></tr
><tr
id=sl_svn7768_2925

><td class="source">            int blu = (ib &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_2926

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2927

><td class="source">            // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_2928

><td class="source">            int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_2929

><td class="source">            int br = (bb &amp; 0xFF0000);  // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_2930

><td class="source">            int bg = (bb &amp; 0xFF00);    // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_2931

><td class="source">            bb = (bb &amp; 0xFF);          // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_2932

><td class="source">            <br></td></tr
><tr
id=sl_svn7768_2933

><td class="source">            m_pixels[xstart] = 0xFF000000 |  <br></td></tr
><tr
id=sl_svn7768_2934

><td class="source">              ((br + (((red - br) * al0) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_2935

><td class="source">              ((bg + (((grn - bg) * al0) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_2936

><td class="source">              ((bb + (((blu - bb) * al0) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_2937

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2938

><td class="source">            // write stencil<br></td></tr
><tr
id=sl_svn7768_2939

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_2940

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_2941

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_2942

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2943

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_2944

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2945

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_2946

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_2947

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_2948

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_2949

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_2950

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_2951

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_2952

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_2953

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_2954

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2955

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_2956

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2957

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_2958

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_2959

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_2960

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_2961

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_2962

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_2963

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_2964

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_2965

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_2966

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2967

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_2968

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2969

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2970

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_2971

><td class="source">   * Texture multiplied with gouraud<br></td></tr
><tr
id=sl_svn7768_2972

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_2973

><td class="source">  private void drawsegment_gouraud_texture24(float leftadd,<br></td></tr
><tr
id=sl_svn7768_2974

><td class="source">                                             float rghtadd,<br></td></tr
><tr
id=sl_svn7768_2975

><td class="source">                                             int ytop,<br></td></tr
><tr
id=sl_svn7768_2976

><td class="source">                                             int ybottom) {<br></td></tr
><tr
id=sl_svn7768_2977

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_2978

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_2979

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_2980

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_2981

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_2982

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_2983

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_2984

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_2985

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_2986

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_2987

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2988

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2989

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_2990

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_2991

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_2992

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_2993

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_2994

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_2995

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_2996

><td class="source"><br></td></tr
><tr
id=sl_svn7768_2997

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2998

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_2999

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_3000

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3001

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_3002

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_3003

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_3004

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_3005

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_3006

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3007

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_3008

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3009

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_3010

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_3011

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3012

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3013

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3014

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3015

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_3016

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3017

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_3018

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3019

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_3020

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_3021

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_3022

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_3023

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_3024

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_3025

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3026

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_3027

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_3028

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3029

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3030

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_3031

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_3032

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_3033

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_3034

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_3035

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3036

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_3037

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3038

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_3039

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_3040

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_3041

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3042

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_3043

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3044

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_3045

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3046

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3047

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_3048

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3049

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3050

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3051

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_3052

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3053

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3054

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3055

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3056

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3057

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_3058

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3059

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3060

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_3061

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3062

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3063

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3064

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3065

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3066

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3067

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_3068

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_3069

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3070

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_3071

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_3072

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_3073

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_3074

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3075

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_3076

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3077

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_3078

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3079

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3080

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_3081

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_3082

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_3083

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3084

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_3085

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3086

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3087

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_3088

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_3089

><td class="source">            m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_3090

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3091

><td class="source">            int red;<br></td></tr
><tr
id=sl_svn7768_3092

><td class="source">            int grn;<br></td></tr
><tr
id=sl_svn7768_3093

><td class="source">            int blu;<br></td></tr
><tr
id=sl_svn7768_3094

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3095

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_3096

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3097

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3098

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3099

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3100

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_3101

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3102

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3103

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3104

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3105

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3106

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3107

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_3108

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3109

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3110

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3111

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3112

><td class="source">              red = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3113

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3114

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_3115

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3116

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3117

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3118

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3119

><td class="source">              grn = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3120

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3121

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_3122

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3123

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3124

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3125

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3126

><td class="source">              blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3127

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_3128

><td class="source">              // get texture pixel color<br></td></tr
><tr
id=sl_svn7768_3129

><td class="source">              blu = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_3130

><td class="source">              red = (blu &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3131

><td class="source">              grn = (blu &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3132

><td class="source">              blu = blu &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_3133

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_3134

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3135

><td class="source">            //<br></td></tr
><tr
id=sl_svn7768_3136

><td class="source">            int r = (ir &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3137

><td class="source">            int g = (ig &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3138

><td class="source">            // oops, namespace collision with accurate <br></td></tr
><tr
id=sl_svn7768_3139

><td class="source">            // texture vector b...sorry [ewjordan]<br></td></tr
><tr
id=sl_svn7768_3140

><td class="source">            int bb2 = (ib &gt;&gt; 16); <br></td></tr
><tr
id=sl_svn7768_3141

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3142

><td class="source">            m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_3143

><td class="source">            ((((red * r) &amp; 0xFF000000) | ((grn * g) &amp; 0xFF0000) | (blu * bb2)) &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn7768_3144

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_3145

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3146

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_3147

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3148

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_3149

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3150

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_3151

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_3152

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_3153

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3154

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_3155

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_3156

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_3157

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_3158

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3159

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3160

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3161

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3162

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_3163

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_3164

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_3165

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_3166

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_3167

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_3168

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_3169

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_3170

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3171

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_3172

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3173

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3174

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_3175

><td class="source">   * Gouraud*texture blended with interpolating alpha<br></td></tr
><tr
id=sl_svn7768_3176

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_3177

><td class="source">  private void drawsegment_gouraud_texture24_alpha<br></td></tr
><tr
id=sl_svn7768_3178

><td class="source">    (<br></td></tr
><tr
id=sl_svn7768_3179

><td class="source">     float leftadd,<br></td></tr
><tr
id=sl_svn7768_3180

><td class="source">     float rghtadd,<br></td></tr
><tr
id=sl_svn7768_3181

><td class="source">     int ytop,<br></td></tr
><tr
id=sl_svn7768_3182

><td class="source">     int ybottom<br></td></tr
><tr
id=sl_svn7768_3183

><td class="source">     ) {<br></td></tr
><tr
id=sl_svn7768_3184

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3185

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_3186

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_3187

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_3188

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_3189

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_3190

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_3191

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_3192

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3193

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3194

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_3195

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3196

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3197

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3198

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_3199

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_3200

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3201

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_3202

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3203

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3204

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3205

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3206

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3207

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_3208

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3209

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_3210

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_3211

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_3212

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_3213

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_3214

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_3215

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3216

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_3217

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3218

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_3219

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_3220

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3221

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3222

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3223

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3224

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_3225

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3226

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_3227

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3228

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_3229

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_3230

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_3231

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_3232

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_3233

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_3234

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_3235

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3236

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_3237

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_3238

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3239

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3240

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_3241

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_3242

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_3243

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_3244

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_3245

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3246

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_3247

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3248

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_3249

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_3250

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_3251

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3252

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_3253

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3254

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_3255

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3256

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3257

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_3258

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3259

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3260

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3261

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_3262

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3263

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3264

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3265

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3266

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3267

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_3268

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3269

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3270

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_3271

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3272

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3273

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3274

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3275

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3276

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3277

><td class="source">      for ( ;xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_3278

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_3279

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3280

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_3281

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_3282

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_3283

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_3284

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3285

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_3286

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3287

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_3288

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3289

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3290

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_3291

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_3292

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_3293

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3294

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_3295

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3296

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3297

><td class="source">        // get texture pixel color<br></td></tr
><tr
id=sl_svn7768_3298

><td class="source">        try<br></td></tr
><tr
id=sl_svn7768_3299

><td class="source">          {<br></td></tr
><tr
id=sl_svn7768_3300

><td class="source">            //if (iz &lt; m_zbuffer[xstart]) {<br></td></tr
><tr
id=sl_svn7768_3301

><td class="source">            if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {  // [fry 041114]<br></td></tr
><tr
id=sl_svn7768_3302

><td class="source">              //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_3303

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3304

><td class="source">              // blend<br></td></tr
><tr
id=sl_svn7768_3305

><td class="source">              int al = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3306

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3307

><td class="source">              int red;<br></td></tr
><tr
id=sl_svn7768_3308

><td class="source">              int grn;<br></td></tr
><tr
id=sl_svn7768_3309

><td class="source">              int blu;<br></td></tr
><tr
id=sl_svn7768_3310

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3311

><td class="source">              if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_3312

><td class="source">                int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3313

><td class="source">                int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3314

><td class="source">                int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3315

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3316

><td class="source">                // get texture pixels<br></td></tr
><tr
id=sl_svn7768_3317

><td class="source">                int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3318

><td class="source">                int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3319

><td class="source">                if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3320

><td class="source">                int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3321

><td class="source">                int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3322

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3323

><td class="source">                // red<br></td></tr
><tr
id=sl_svn7768_3324

><td class="source">                int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3325

><td class="source">                int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3326

><td class="source">                int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3327

><td class="source">                int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3328

><td class="source">                red = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3329

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3330

><td class="source">                // grn<br></td></tr
><tr
id=sl_svn7768_3331

><td class="source">                red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3332

><td class="source">                red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3333

><td class="source">                up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3334

><td class="source">                dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3335

><td class="source">                grn = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3336

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3337

><td class="source">                // blu<br></td></tr
><tr
id=sl_svn7768_3338

><td class="source">                red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3339

><td class="source">                red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3340

><td class="source">                up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3341

><td class="source">                dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3342

><td class="source">                blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3343

><td class="source">              } else {<br></td></tr
><tr
id=sl_svn7768_3344

><td class="source">                blu = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_3345

><td class="source">                red = (blu &amp; 0xFF0000) &gt;&gt; 16; // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3346

><td class="source">                grn = (blu &amp; 0xFF00) &gt;&gt; 8;    // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3347

><td class="source">                blu = (blu &amp; 0xFF);       // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3348

><td class="source">              }<br></td></tr
><tr
id=sl_svn7768_3349

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3350

><td class="source">              // multiply with gouraud color<br></td></tr
><tr
id=sl_svn7768_3351

><td class="source">              red = (red * ir) &gt;&gt;&gt; 8;   // 0x00FF????<br></td></tr
><tr
id=sl_svn7768_3352

><td class="source">              grn = (grn * ig) &gt;&gt;&gt; 16;  // 0x0000FF??<br></td></tr
><tr
id=sl_svn7768_3353

><td class="source">              blu = (blu * ib) &gt;&gt;&gt; 24;  // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3354

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3355

><td class="source">              // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_3356

><td class="source">              int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_3357

><td class="source">              int br = (bb &amp; 0xFF0000); // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_3358

><td class="source">              int bg = (bb &amp; 0xFF00);   // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_3359

><td class="source">              bb = (bb &amp; 0xFF);         // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3360

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3361

><td class="source">              //<br></td></tr
><tr
id=sl_svn7768_3362

><td class="source">              m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_3363

><td class="source">                ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_3364

><td class="source">                ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_3365

><td class="source">                ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3366

><td class="source">//              m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_3367

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_3368

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3369

><td class="source">        catch (Exception e) {<br></td></tr
><tr
id=sl_svn7768_3370

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3371

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3372

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_3373

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3374

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_3375

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_3376

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_3377

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3378

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_3379

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_3380

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_3381

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_3382

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_3383

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3384

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3385

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3386

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3387

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3388

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_3389

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_3390

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_3391

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_3392

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_3393

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_3394

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_3395

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_3396

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_3397

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3398

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_3399

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3400

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3401

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_3402

><td class="source">   * Gouraud*texture blended with interpolating alpha<br></td></tr
><tr
id=sl_svn7768_3403

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_3404

><td class="source">  private void drawsegment_gouraud_texture32<br></td></tr
><tr
id=sl_svn7768_3405

><td class="source">    (<br></td></tr
><tr
id=sl_svn7768_3406

><td class="source">     float leftadd,<br></td></tr
><tr
id=sl_svn7768_3407

><td class="source">     float rghtadd,<br></td></tr
><tr
id=sl_svn7768_3408

><td class="source">     int ytop,<br></td></tr
><tr
id=sl_svn7768_3409

><td class="source">     int ybottom<br></td></tr
><tr
id=sl_svn7768_3410

><td class="source">     ) {<br></td></tr
><tr
id=sl_svn7768_3411

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3412

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_3413

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_3414

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_3415

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_3416

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_3417

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_3418

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_3419

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3420

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3421

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_3422

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3423

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3424

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3425

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_3426

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_3427

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3428

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_3429

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3430

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3431

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3432

><td class="source">    ytop*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3433

><td class="source">    ybottom*=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3434

><td class="source">    //int p = m_index;<br></td></tr
><tr
id=sl_svn7768_3435

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3436

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_3437

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_3438

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_3439

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_3440

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_3441

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3442

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_3443

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3444

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_3445

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_3446

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3447

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3448

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3449

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3450

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_3451

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3452

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_3453

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3454

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_3455

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_3456

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_3457

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_3458

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_3459

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_3460

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3461

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_3462

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_3463

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3464

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_3465

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_3466

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_3467

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_3468

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_3469

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3470

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_3471

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3472

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_3473

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_3474

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_3475

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3476

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_3477

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3478

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_3479

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3480

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3481

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_3482

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3483

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3484

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3485

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_3486

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3487

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3488

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3489

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3490

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3491

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_3492

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3493

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3494

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_3495

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3496

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3497

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3498

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3499

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3500

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3501

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3502

><td class="source">      for ( ; xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_3503

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_3504

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3505

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_3506

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_3507

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_3508

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_3509

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3510

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_3511

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3512

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_3513

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3514

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3515

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_3516

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_3517

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_3518

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3519

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_3520

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3521

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3522

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_3523

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {<br></td></tr
><tr
id=sl_svn7768_3524

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_3525

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3526

><td class="source">            int red;<br></td></tr
><tr
id=sl_svn7768_3527

><td class="source">            int grn;<br></td></tr
><tr
id=sl_svn7768_3528

><td class="source">            int blu;<br></td></tr
><tr
id=sl_svn7768_3529

><td class="source">            int al;<br></td></tr
><tr
id=sl_svn7768_3530

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3531

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_3532

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3533

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3534

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3535

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3536

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_3537

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3538

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3539

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3540

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3541

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3542

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3543

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_3544

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3545

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3546

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3547

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3548

><td class="source">              red = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3549

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3550

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_3551

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3552

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3553

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3554

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3555

><td class="source">              grn = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3556

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3557

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_3558

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3559

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3560

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3561

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3562

><td class="source">              blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3563

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3564

><td class="source">              // alpha<br></td></tr
><tr
id=sl_svn7768_3565

><td class="source">              pix0&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_3566

><td class="source">              pix2&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_3567

><td class="source">              up = pix0 + ((((pix1 &gt;&gt;&gt; 24) - pix0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3568

><td class="source">              dn = pix2 + ((((pix3 &gt;&gt;&gt; 24) - pix2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3569

><td class="source">              al = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3570

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_3571

><td class="source">              // get texture pixel color<br></td></tr
><tr
id=sl_svn7768_3572

><td class="source">              blu = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_3573

><td class="source">              al = (blu &gt;&gt;&gt; 24);<br></td></tr
><tr
id=sl_svn7768_3574

><td class="source">              red = (blu &amp; 0xFF0000) &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3575

><td class="source">              grn = (blu &amp; 0xFF00) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3576

><td class="source">              blu = blu &amp; 0xFF;<br></td></tr
><tr
id=sl_svn7768_3577

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_3578

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3579

><td class="source">            // multiply with gouraud color<br></td></tr
><tr
id=sl_svn7768_3580

><td class="source">            red = (red * ir) &gt;&gt;&gt; 8;   // 0x00FF????<br></td></tr
><tr
id=sl_svn7768_3581

><td class="source">            grn = (grn * ig) &gt;&gt;&gt; 16;  // 0x0000FF??<br></td></tr
><tr
id=sl_svn7768_3582

><td class="source">            blu = (blu * ib) &gt;&gt;&gt; 24;  // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3583

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3584

><td class="source">            // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_3585

><td class="source">            int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_3586

><td class="source">            int br = (bb &amp; 0xFF0000); // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_3587

><td class="source">            int bg = (bb &amp; 0xFF00);   // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_3588

><td class="source">            bb = (bb &amp; 0xFF);         // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3589

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3590

><td class="source">            //<br></td></tr
><tr
id=sl_svn7768_3591

><td class="source">            m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_3592

><td class="source">            ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_3593

><td class="source">            ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_3594

><td class="source">            ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3595

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3596

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_3597

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3598

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_3599

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3600

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_3601

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_3602

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_3603

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3604

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_3605

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_3606

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_3607

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_3608

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3609

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3610

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3611

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_3612

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_3613

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_3614

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_3615

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_3616

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_3617

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_3618

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_3619

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3620

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_3621

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3622

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3623

><td class="source">  /**<br></td></tr
><tr
id=sl_svn7768_3624

><td class="source">   * Gouraud*texture blended with interpolating alpha<br></td></tr
><tr
id=sl_svn7768_3625

><td class="source">   */<br></td></tr
><tr
id=sl_svn7768_3626

><td class="source">  private void drawsegment_gouraud_texture32_alpha<br></td></tr
><tr
id=sl_svn7768_3627

><td class="source">    (<br></td></tr
><tr
id=sl_svn7768_3628

><td class="source">     float leftadd,<br></td></tr
><tr
id=sl_svn7768_3629

><td class="source">     float rghtadd,<br></td></tr
><tr
id=sl_svn7768_3630

><td class="source">     int ytop,<br></td></tr
><tr
id=sl_svn7768_3631

><td class="source">     int ybottom<br></td></tr
><tr
id=sl_svn7768_3632

><td class="source">     ) {<br></td></tr
><tr
id=sl_svn7768_3633

><td class="source">    //Accurate texture mode added - comments stripped from dupe code, see drawsegment_texture24() for details<br></td></tr
><tr
id=sl_svn7768_3634

><td class="source">    int ypixel = ytop;<br></td></tr
><tr
id=sl_svn7768_3635

><td class="source">    int lastRowStart = m_texture.length - TEX_WIDTH - 2;<br></td></tr
><tr
id=sl_svn7768_3636

><td class="source">    boolean accurateMode = parent.hints[ENABLE_ACCURATE_TEXTURES];<br></td></tr
><tr
id=sl_svn7768_3637

><td class="source">    float screenx = 0; float screeny = 0; float screenz = 0;<br></td></tr
><tr
id=sl_svn7768_3638

><td class="source">    float a = 0; float b = 0; float c = 0;<br></td></tr
><tr
id=sl_svn7768_3639

><td class="source">    int linearInterpPower = TEX_INTERP_POWER;<br></td></tr
><tr
id=sl_svn7768_3640

><td class="source">    int linearInterpLength = 1 &lt;&lt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3641

><td class="source">    if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3642

><td class="source">      if(precomputeAccurateTexturing()){ //see if the precomputation goes well, if so finish the setup<br></td></tr
><tr
id=sl_svn7768_3643

><td class="source">        newax *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3644

><td class="source">        newbx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3645

><td class="source">        newcx *= linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3646

><td class="source">        screenz = nearPlaneDepth;<br></td></tr
><tr
id=sl_svn7768_3647

><td class="source">        firstSegment = false;<br></td></tr
><tr
id=sl_svn7768_3648

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3649

><td class="source">        accurateMode = false; //if the matrix inversion screwed up, revert to normal rendering (something is degenerate)<br></td></tr
><tr
id=sl_svn7768_3650

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3651

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3652

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3653

><td class="source">    ytop *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3654

><td class="source">    ybottom *= SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3655

><td class="source">//    int p = m_index;<br></td></tr
><tr
id=sl_svn7768_3656

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3657

><td class="source">    float iuf = iuadd;<br></td></tr
><tr
id=sl_svn7768_3658

><td class="source">    float ivf = ivadd;<br></td></tr
><tr
id=sl_svn7768_3659

><td class="source">    float irf = iradd;<br></td></tr
><tr
id=sl_svn7768_3660

><td class="source">    float igf = igadd;<br></td></tr
><tr
id=sl_svn7768_3661

><td class="source">    float ibf = ibadd;<br></td></tr
><tr
id=sl_svn7768_3662

><td class="source">    float iaf = iaadd;<br></td></tr
><tr
id=sl_svn7768_3663

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3664

><td class="source">    while (ytop &lt; ybottom) {<br></td></tr
><tr
id=sl_svn7768_3665

><td class="source">      int xstart = (int) (xleft + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3666

><td class="source">      if (xstart &lt; 0)<br></td></tr
><tr
id=sl_svn7768_3667

><td class="source">        xstart = 0;<br></td></tr
><tr
id=sl_svn7768_3668

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3669

><td class="source">      int xpixel = xstart;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3670

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3671

><td class="source">      int xend = (int) (xrght + PIXEL_CENTER);<br></td></tr
><tr
id=sl_svn7768_3672

><td class="source">      if (xend &gt; SCREEN_WIDTH)<br></td></tr
><tr
id=sl_svn7768_3673

><td class="source">        xend = SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3674

><td class="source">      float xdiff = (xstart + PIXEL_CENTER) - xleft;<br></td></tr
><tr
id=sl_svn7768_3675

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3676

><td class="source">      int iu = (int) (iuf * xdiff + uleft);<br></td></tr
><tr
id=sl_svn7768_3677

><td class="source">      int iv = (int) (ivf * xdiff + vleft);<br></td></tr
><tr
id=sl_svn7768_3678

><td class="source">      int ir = (int) (irf * xdiff + rleft);<br></td></tr
><tr
id=sl_svn7768_3679

><td class="source">      int ig = (int) (igf * xdiff + gleft);<br></td></tr
><tr
id=sl_svn7768_3680

><td class="source">      int ib = (int) (ibf * xdiff + bleft);<br></td></tr
><tr
id=sl_svn7768_3681

><td class="source">      int ia = (int) (iaf * xdiff + aleft);<br></td></tr
><tr
id=sl_svn7768_3682

><td class="source">      float iz = izadd * xdiff + zleft;<br></td></tr
><tr
id=sl_svn7768_3683

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3684

><td class="source">      xstart+=ytop;<br></td></tr
><tr
id=sl_svn7768_3685

><td class="source">      xend+=ytop;<br></td></tr
><tr
id=sl_svn7768_3686

><td class="source">      if (accurateMode){<br></td></tr
><tr
id=sl_svn7768_3687

><td class="source">        screenx = xmult*(xpixel+.5f-(SCREEN_WIDTH/2.0f));<br></td></tr
><tr
id=sl_svn7768_3688

><td class="source">        screeny = ymult*(ypixel+.5f-(SCREEN_HEIGHT/2.0f));<br></td></tr
><tr
id=sl_svn7768_3689

><td class="source">        a = screenx*ax+screeny*ay+screenz*az;<br></td></tr
><tr
id=sl_svn7768_3690

><td class="source">        b = screenx*bx+screeny*by+screenz*bz;<br></td></tr
><tr
id=sl_svn7768_3691

><td class="source">        c = screenx*cx+screeny*cy+screenz*cz;<br></td></tr
><tr
id=sl_svn7768_3692

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3693

><td class="source">      boolean goingIn = ( (newcx &gt; 0) == (c &gt; 0) )?false:true;<br></td></tr
><tr
id=sl_svn7768_3694

><td class="source">      int interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3695

><td class="source">      int deltaU = 0; int deltaV = 0;<br></td></tr
><tr
id=sl_svn7768_3696

><td class="source">      float fu = 0; float fv = 0;<br></td></tr
><tr
id=sl_svn7768_3697

><td class="source">      float oldfu = 0; float oldfv = 0;<br></td></tr
><tr
id=sl_svn7768_3698

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3699

><td class="source">      if (accurateMode&amp;&amp;goingIn){<br></td></tr
><tr
id=sl_svn7768_3700

><td class="source">        int rightOffset = (xend-xstart-1)%linearInterpLength;<br></td></tr
><tr
id=sl_svn7768_3701

><td class="source">        int leftOffset = linearInterpLength-rightOffset;<br></td></tr
><tr
id=sl_svn7768_3702

><td class="source">        float rightOffset2 = rightOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3703

><td class="source">        float leftOffset2 = leftOffset / ((float)linearInterpLength);<br></td></tr
><tr
id=sl_svn7768_3704

><td class="source">        interpCounter = leftOffset;<br></td></tr
><tr
id=sl_svn7768_3705

><td class="source">        float ao = a-leftOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3706

><td class="source">        float bo = b-leftOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3707

><td class="source">        float co = c-leftOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3708

><td class="source">        float oneoverc = 65536.0f/co;<br></td></tr
><tr
id=sl_svn7768_3709

><td class="source">        oldfu = (ao*oneoverc); oldfv = (bo*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3710

><td class="source">        a += rightOffset2*newax;<br></td></tr
><tr
id=sl_svn7768_3711

><td class="source">        b += rightOffset2*newbx;<br></td></tr
><tr
id=sl_svn7768_3712

><td class="source">        c += rightOffset2*newcx;<br></td></tr
><tr
id=sl_svn7768_3713

><td class="source">        oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3714

><td class="source">        fu = a*oneoverc; fv = b*oneoverc;<br></td></tr
><tr
id=sl_svn7768_3715

><td class="source">        deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3716

><td class="source">        deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3717

><td class="source">        iu = ( (int)oldfu )+(leftOffset-1)*deltaU; iv = ( (int)oldfv )+(leftOffset-1)*deltaV; //another &quot;off-by-one&quot; hack<br></td></tr
><tr
id=sl_svn7768_3718

><td class="source">      } else{<br></td></tr
><tr
id=sl_svn7768_3719

><td class="source">        float preoneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3720

><td class="source">        fu = (a*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3721

><td class="source">        fv = (b*preoneoverc);<br></td></tr
><tr
id=sl_svn7768_3722

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3723

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3724

><td class="source">      for ( ;xstart &lt; xend; xstart++ ) {<br></td></tr
><tr
id=sl_svn7768_3725

><td class="source">        if(accurateMode){<br></td></tr
><tr
id=sl_svn7768_3726

><td class="source">          if (interpCounter == linearInterpLength) interpCounter = 0;<br></td></tr
><tr
id=sl_svn7768_3727

><td class="source">          if (interpCounter == 0){<br></td></tr
><tr
id=sl_svn7768_3728

><td class="source">            a += newax;<br></td></tr
><tr
id=sl_svn7768_3729

><td class="source">            b += newbx;<br></td></tr
><tr
id=sl_svn7768_3730

><td class="source">            c += newcx;<br></td></tr
><tr
id=sl_svn7768_3731

><td class="source">            float oneoverc = 65536.0f/c;<br></td></tr
><tr
id=sl_svn7768_3732

><td class="source">            oldfu = fu; oldfv = fv;<br></td></tr
><tr
id=sl_svn7768_3733

><td class="source">            fu = (a*oneoverc); fv = (b*oneoverc);<br></td></tr
><tr
id=sl_svn7768_3734

><td class="source">            iu = (int)oldfu; iv = (int)oldfv;<br></td></tr
><tr
id=sl_svn7768_3735

><td class="source">            deltaU = ((int)(fu - oldfu)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3736

><td class="source">            deltaV = ((int)(fv - oldfv)) &gt;&gt; linearInterpPower;<br></td></tr
><tr
id=sl_svn7768_3737

><td class="source">          } else{<br></td></tr
><tr
id=sl_svn7768_3738

><td class="source">            iu += deltaU;<br></td></tr
><tr
id=sl_svn7768_3739

><td class="source">            iv += deltaV;<br></td></tr
><tr
id=sl_svn7768_3740

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3741

><td class="source">          interpCounter++;<br></td></tr
><tr
id=sl_svn7768_3742

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3743

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3744

><td class="source">        // get texture pixel color<br></td></tr
><tr
id=sl_svn7768_3745

><td class="source">        try {<br></td></tr
><tr
id=sl_svn7768_3746

><td class="source">          //if (iz &lt; m_zbuffer[xstart]) {<br></td></tr
><tr
id=sl_svn7768_3747

><td class="source">          if (noDepthTest || (iz &lt;= m_zbuffer[xstart])) {  // [fry 041114]<br></td></tr
><tr
id=sl_svn7768_3748

><td class="source">            //m_zbuffer[xstart] = iz;<br></td></tr
><tr
id=sl_svn7768_3749

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3750

><td class="source">            // blend<br></td></tr
><tr
id=sl_svn7768_3751

><td class="source">            int al = ia &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3752

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3753

><td class="source">            int red;<br></td></tr
><tr
id=sl_svn7768_3754

><td class="source">            int grn;<br></td></tr
><tr
id=sl_svn7768_3755

><td class="source">            int blu;<br></td></tr
><tr
id=sl_svn7768_3756

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3757

><td class="source">            if (m_bilinear) {<br></td></tr
><tr
id=sl_svn7768_3758

><td class="source">              int ofs = (iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16);<br></td></tr
><tr
id=sl_svn7768_3759

><td class="source">              int iui = (iu &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3760

><td class="source">              int ivi = (iv &amp; 0xFFFF) &gt;&gt; 9;<br></td></tr
><tr
id=sl_svn7768_3761

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3762

><td class="source">              // get texture pixels<br></td></tr
><tr
id=sl_svn7768_3763

><td class="source">              int pix0 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3764

><td class="source">              int pix1 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3765

><td class="source">              if (ofs &lt; lastRowStart) ofs+=TEX_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3766

><td class="source">              int pix2 = m_texture[ofs];<br></td></tr
><tr
id=sl_svn7768_3767

><td class="source">              int pix3 = m_texture[ofs + 1];<br></td></tr
><tr
id=sl_svn7768_3768

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3769

><td class="source">              // red<br></td></tr
><tr
id=sl_svn7768_3770

><td class="source">              int red0 = (pix0 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3771

><td class="source">              int red2 = (pix2 &amp; 0xFF0000);<br></td></tr
><tr
id=sl_svn7768_3772

><td class="source">              int up = red0 + ((((pix1 &amp; 0xFF0000) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3773

><td class="source">              int dn = red2 + ((((pix3 &amp; 0xFF0000) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3774

><td class="source">              red = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn7768_3775

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3776

><td class="source">              // grn<br></td></tr
><tr
id=sl_svn7768_3777

><td class="source">              red0 = (pix0 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3778

><td class="source">              red2 = (pix2 &amp; 0xFF00);<br></td></tr
><tr
id=sl_svn7768_3779

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF00) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3780

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF00) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3781

><td class="source">              grn = (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3782

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3783

><td class="source">              // blu<br></td></tr
><tr
id=sl_svn7768_3784

><td class="source">              red0 = (pix0 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3785

><td class="source">              red2 = (pix2 &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3786

><td class="source">              up = red0 + ((((pix1 &amp; 0xFF) - red0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3787

><td class="source">              dn = red2 + ((((pix3 &amp; 0xFF) - red2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3788

><td class="source">              blu = up + (((dn-up) * ivi) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3789

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3790

><td class="source">              // alpha<br></td></tr
><tr
id=sl_svn7768_3791

><td class="source">              pix0&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_3792

><td class="source">              pix2&gt;&gt;&gt;=24;<br></td></tr
><tr
id=sl_svn7768_3793

><td class="source">              up = pix0 + ((((pix1 &gt;&gt;&gt; 24) - pix0) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3794

><td class="source">              dn = pix2 + ((((pix3 &gt;&gt;&gt; 24) - pix2) * iui) &gt;&gt; 7);<br></td></tr
><tr
id=sl_svn7768_3795

><td class="source">              al = al * (up + (((dn-up) * ivi) &gt;&gt; 7)) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3796

><td class="source">            } else {<br></td></tr
><tr
id=sl_svn7768_3797

><td class="source">              blu = m_texture[(iv &gt;&gt; 16) * TEX_WIDTH + (iu &gt;&gt; 16)];<br></td></tr
><tr
id=sl_svn7768_3798

><td class="source">              al = al * (blu &gt;&gt;&gt; 24) &gt;&gt; 8;<br></td></tr
><tr
id=sl_svn7768_3799

><td class="source">              red = (blu &amp; 0xFF0000) &gt;&gt; 16; // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3800

><td class="source">              grn = (blu &amp; 0xFF00) &gt;&gt; 8;    // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3801

><td class="source">              blu = (blu &amp; 0xFF);       // 0 - 255<br></td></tr
><tr
id=sl_svn7768_3802

><td class="source">            }<br></td></tr
><tr
id=sl_svn7768_3803

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3804

><td class="source">            // multiply with gouraud color<br></td></tr
><tr
id=sl_svn7768_3805

><td class="source">            red = (red * ir) &gt;&gt;&gt; 8;   // 0x00FF????<br></td></tr
><tr
id=sl_svn7768_3806

><td class="source">            grn = (grn * ig) &gt;&gt;&gt; 16;  // 0x0000FF??<br></td></tr
><tr
id=sl_svn7768_3807

><td class="source">            blu = (blu * ib) &gt;&gt;&gt; 24;  // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3808

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3809

><td class="source">            // get buffer pixels<br></td></tr
><tr
id=sl_svn7768_3810

><td class="source">            int bb = m_pixels[xstart];<br></td></tr
><tr
id=sl_svn7768_3811

><td class="source">            int br = (bb &amp; 0xFF0000); // 0x00FF0000<br></td></tr
><tr
id=sl_svn7768_3812

><td class="source">            int bg = (bb &amp; 0xFF00);   // 0x0000FF00<br></td></tr
><tr
id=sl_svn7768_3813

><td class="source">            bb = (bb &amp; 0xFF);         // 0x000000FF<br></td></tr
><tr
id=sl_svn7768_3814

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3815

><td class="source">            //<br></td></tr
><tr
id=sl_svn7768_3816

><td class="source">            m_pixels[xstart] = 0xFF000000 | <br></td></tr
><tr
id=sl_svn7768_3817

><td class="source">              ((br + (((red - br) * al) &gt;&gt; 8)) &amp; 0xFF0000) |<br></td></tr
><tr
id=sl_svn7768_3818

><td class="source">              ((bg + (((grn - bg) * al) &gt;&gt; 8)) &amp; 0xFF00) | <br></td></tr
><tr
id=sl_svn7768_3819

><td class="source">              ((bb + (((blu - bb) * al) &gt;&gt; 8)) &amp; 0xFF);<br></td></tr
><tr
id=sl_svn7768_3820

><td class="source">//            m_stencil[xstart] = p;<br></td></tr
><tr
id=sl_svn7768_3821

><td class="source">          }<br></td></tr
><tr
id=sl_svn7768_3822

><td class="source">        } catch (Exception e) { }<br></td></tr
><tr
id=sl_svn7768_3823

><td class="source"><br></td></tr
><tr
id=sl_svn7768_3824

><td class="source">        //<br></td></tr
><tr
id=sl_svn7768_3825

><td class="source">        xpixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3826

><td class="source">        if (!accurateMode){<br></td></tr
><tr
id=sl_svn7768_3827

><td class="source">          iu+=iuadd;<br></td></tr
><tr
id=sl_svn7768_3828

><td class="source">          iv+=ivadd;<br></td></tr
><tr
id=sl_svn7768_3829

><td class="source">        }<br></td></tr
><tr
id=sl_svn7768_3830

><td class="source">        ir+=iradd;<br></td></tr
><tr
id=sl_svn7768_3831

><td class="source">        ig+=igadd;<br></td></tr
><tr
id=sl_svn7768_3832

><td class="source">        ib+=ibadd;<br></td></tr
><tr
id=sl_svn7768_3833

><td class="source">        ia+=iaadd;<br></td></tr
><tr
id=sl_svn7768_3834

><td class="source">        iz+=izadd;<br></td></tr
><tr
id=sl_svn7768_3835

><td class="source">      }<br></td></tr
><tr
id=sl_svn7768_3836

><td class="source">      ypixel++;//accurate mode<br></td></tr
><tr
id=sl_svn7768_3837

><td class="source">      ytop+=SCREEN_WIDTH;<br></td></tr
><tr
id=sl_svn7768_3838

><td class="source">      xleft+=leftadd;<br></td></tr
><tr
id=sl_svn7768_3839

><td class="source">      xrght+=rghtadd;<br></td></tr
><tr
id=sl_svn7768_3840

><td class="source">      uleft+=uleftadd;<br></td></tr
><tr
id=sl_svn7768_3841

><td class="source">      vleft+=vleftadd;<br></td></tr
><tr
id=sl_svn7768_3842

><td class="source">      rleft+=rleftadd;<br></td></tr
><tr
id=sl_svn7768_3843

><td class="source">      gleft+=gleftadd;<br></td></tr
><tr
id=sl_svn7768_3844

><td class="source">      bleft+=bleftadd;<br></td></tr
><tr
id=sl_svn7768_3845

><td class="source">      aleft+=aleftadd;<br></td></tr
><tr
id=sl_svn7768_3846

><td class="source">      zleft+=zleftadd;<br></td></tr
><tr
id=sl_svn7768_3847

><td class="source">    }<br></td></tr
><tr
id=sl_svn7768_3848

><td class="source">  }<br></td></tr
><tr
id=sl_svn7768_3849

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
 <a href="/p/processing/source/detail?spec=svn7768&r=7538">r7538</a>
 by e.e.coli
 on Dec 24, 2010
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=7538&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old_path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old=4742">Diff</a>
 </div>
 <pre>Remove apparent logic bug in PTriangle.</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/processing/source/detail?r=7538&spec=svn7768';
 var publish_url = '/p/processing/source/detail?r=7538&spec=svn7768#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/processing/core/src/processing/core/PTriangle.java');
 changed_urls.push('/p/processing/source/browse/trunk/processing/core/src/processing/core/PTriangle.java?r\x3d7538\x26spec\x3dsvn7768');
 
 var selected_path = '/trunk/processing/core/src/processing/core/PTriangle.java';
 
 
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
 
 <option value="/p/processing/source/browse/trunk/processing/core/src/processing/core/PTriangle.java?r=7538&amp;spec=svn7768"
 selected="selected"
 >...c/processing/core/PTriangle.java</option>
 
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
 <a href="/p/processing/source/detail?spec=svn7768&r=4742">r4742</a>
 by fry
 on Oct 08, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=4742&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old_path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old=4736">Diff</a>
 <br>
 <pre class="ifOpened">working on shape methods
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=4736">r4736</a>
 by fry
 on Oct 08, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=4736&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old_path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old=4688">Diff</a>
 <br>
 <pre class="ifOpened">debugging lots of minor breakage from
major overhaul of the last two weeks
</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/processing/source/detail?spec=svn7768&r=4688">r4688</a>
 by fry
 on Sep 28, 2008
 &nbsp; <a href="/p/processing/source/diff?spec=svn7768&r=4688&amp;format=side&amp;path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old_path=/trunk/processing/core/src/processing/core/PTriangle.java&amp;old=4299">Diff</a>
 <br>
 <pre class="ifOpened">working on pgraphics/pshape cleanup
</pre>
 </div>
 
 
 <a href="/p/processing/source/list?path=/trunk/processing/core/src/processing/core/PTriangle.java&start=7538">All revisions of this file</a>
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
 
 <div>Size: 130028 bytes,
 3849 lines</div>
 
 <div><a href="http://processing.googlecode.com/svn/trunk/processing/core/src/processing/core/PTriangle.java">View raw file</a></div>
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
 var paths = {'svn7768': '/trunk/processing/core/src/processing/core/PTriangle.java'}
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

