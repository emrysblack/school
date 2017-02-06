<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="bsa">
  <html>
  <body style = "background-color:#E5E4D7;"><!--"background-color:#d0e4fe;">-->
  <h2>Scouts</h2>
  <xsl:apply-templates/>
  </body>
  </html>
</xsl:template>

<xsl:template match="council">
  <h2 style="clear:both;"><xsl:value-of select="@name"/></h2>
  <xsl:apply-templates/>
  <br/>
  
</xsl:template>

<xsl:template match="troop">
  <table border="0" style="float:left;">
    <tr bgcolor="#9acd32">
      <th colspan ="3"><xsl:value-of select="@unitName"/></th>
    </tr>
    <xsl:apply-templates><xsl:sort select="lastName"/>
    </xsl:apply-templates>
  </table>
</xsl:template>

<xsl:template match="scout">
  <tr>
    <td><b><xsl:value-of select="firstName"/>
    <xsl:text>&#160;</xsl:text>
    <xsl:value-of select="lastName"/></b></td>
    <td><select><xsl:apply-templates select="rank"/></select></td>
    <td><select><xsl:apply-templates select="meritbadge"/></select></td>
  </tr>
  <tr>
    <td><i><xsl:value-of select="phone"/></i></td>
  </tr>
  <xsl:apply-templates select="address"/>
</xsl:template>

<xsl:template match="rank">
  <option><xsl:value-of select="."/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@date-earned"/></option>
</xsl:template>

<xsl:template match="meritbadge">
  <option><xsl:value-of select="."/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@date-earned"/></option>
</xsl:template>

<xsl:template match="address">
   <tr>
      <td><xsl:value-of select="street"/></td>
   </tr>
   <tr>
      <td><xsl:value-of select="city"/><xsl:text>, </xsl:text><xsl:value-of select="state"/></td>
   </tr>
   <tr><td><br/></td></tr>
</xsl:template>
</xsl:stylesheet> 
