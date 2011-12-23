<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0"
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
        >
<xsl:template match="/">

	<html>
        <head>
	<title>
	Imports 
	</title>
	<style type="text/css">
	H2 { font-weight: bold; 
  		font-size: 16pt;
  		line-height: 14pt; 
  		font-family: helvetica; 
  		font-variant: normal;
  		font-style: normal; 
	   }
	</style>
	</head>
<body>
	<xsl:apply-templates/>	
</body>
</html>
</xsl:template>
<xsl:template match="testRun">
	<table border="1" cellpadding="5" bgcolor="99CCFF"><td valign="top">
		<h2>Date: <xsl:value-of select="@date "/></h2>
		<h2>Time: <xsl:value-of select="@time "/></h2>
		<h2>User: <xsl:value-of select="@user"/></h2>
		<h2>Target: <xsl:value-of select="@target"/></h2>
		<h2>Platform: <xsl:value-of select="@platform"/></h2>
        <h2>Path: <xsl:value-of select="@path"/></h2>
        <h2>Tests Passed: <xsl:value-of select="@testsPassed"/></h2>
        <h2>Total Tests: <xsl:value-of select="@totalTests"/></h2>
		<xsl:apply-templates/>
	</td></table>
</xsl:template>
<xsl:template match="tree-imports" >
	<table border="1" cellpadding="5" bgcolor="FFFFFF">
		<tr><th>Tools Version </th><th>Import path</th></tr>
		<tr><td><xsl:value-of select="tools-version"/></td>
		<td><xsl:value-of select="tools-version/@TOOLS_SETTING"/></td></tr>
		<tr><th>File Name </th><th>Imported Tree Name</th></tr>
		<xsl:for-each select="import">
		<tr>
		<td><xsl:value-of select="name"/></td>
		<td><xsl:value-of select="location"/></td>
		</tr>
	</xsl:for-each>
	</table>
</xsl:template>
<xsl:template match="testPackage">
	<h3><xsl:value-of select="@name"/></h3>
	<table border="1" cellpadding="5" bgcolor="FFFFFF">
		<tr><th>File under test</th><th>Result</th><th>Args</th></tr>
		<xsl:apply-templates/>	
	</table>
</xsl:template>
<xsl:template match="test[@result='pass']">
	<tr>
	<td valign="left"><xsl:value-of select="@name"/></td>
	<td valign="center" bgcolor="green"><xsl:value-of select="@result"/></td>
    <td valign="left"><xsl:value-of select="@argsToMain"/></td>
	</tr>
</xsl:template>
<xsl:template match="test[@result='fail']">
	<tr>
	<td align="left"><xsl:value-of select="@name"/></td>
	<td align="center" bgcolor="red"><xsl:value-of select="@result"/></td>
    <td valign="left"><xsl:value-of select="@argsToMain"/></td>
	</tr>
</xsl:template>
<xsl:template match="test[@result='timeout (60000 ms)']">
	<tr>
	<td align="left"><xsl:value-of select="@name"/></td>
	<td align="center" bgcolor="red"><xsl:value-of select="@result"/></td>
    <td valign="left"><xsl:value-of select="@argsToMain"/></td>
	</tr>
</xsl:template>
<xsl:template match="test[@result='.k file not found']">
	<tr>
	<td align="left"><xsl:value-of select="@name"/></td>
	<td align="center" bgcolor="yellow"><xsl:value-of select="@result"/></td>
    <td valign="left"><xsl:value-of select="@argsToMain"/></td>
	</tr>
</xsl:template>
<xsl:template match="test[@result='.out file not found']">
	<tr>
	<td align="left"><xsl:value-of select="@name"/></td>
	<td align="center" bgcolor="yellow"><xsl:value-of select="@result"/></td>
    <td valign="left"><xsl:value-of select="@argsToMain"/></td>
	</tr>
</xsl:template>
</xsl:stylesheet>
