<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="studentList">
  <html>
  <body style = "background-color:#d0e4fe">
  <h2 style = "text-align:center">Student List</h2>
  <table style = "margin:auto;  border:3px solid black">
    <tr bgcolor="#9acd32">
      <th>Student</th>
      <th>Location</th>
      <th>School</th>
      <th>Department</th>
      <th>Major</th>
    </tr>
    <xsl:apply-templates/>
  </table>
  </body>
  </html>
</xsl:template>

<xsl:template match="student">
  <tr style = "background-color:white">
    <td style = "text-align:center">
      <xsl:value-of select="name/first"/>
      <xsl:text>&#160;</xsl:text>
      <xsl:value-of select="name/middle"/>
      <xsl:text>&#160;</xsl:text>
      <xsl:value-of select="name/last"/>
    </td>
    <td style = "text-align:center">
      <xsl:value-of select="location/city"/>
      <xsl:text>,&#160;</xsl:text>
      <xsl:value-of select="location/state"/>
    </td>
    <td style = "text-align:center">
      <xsl:value-of select="college/@name"/>
    </td>
    <td style = "text-align:center">
      <xsl:value-of select="college/department/@name"/>
    </td>
    <td style = "text-align:center">
      <xsl:value-of select="college/department/major/@id"/>
      <xsl:text>&#160;</xsl:text>
      <xsl:value-of select="college/department/major"/>
    </td>
    <!--<xsl:apply-templates/>-->
  </tr>
</xsl:template>


</xsl:stylesheet> 
