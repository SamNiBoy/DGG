SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[storage]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[storage](
	[boxid] [nvarchar](50) NOT NULL,
	[itemid] [nvarchar](50) NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[price] [float] NOT NULL,
	[qty] [int] NOT NULL,
	[description] [nvarchar](300) NULL,
 CONSTRAINT [PK_storage] PRIMARY KEY CLUSTERED 
(
	[boxid] ASC,
	[itemid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[sale]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[sale](
	[saleid] [nvarchar](50) NOT NULL,
	[boxid] [nvarchar](50) NOT NULL,
	[itemid] [nvarchar](50) NOT NULL,
	[itemname] [nvarchar](50) NOT NULL,
	[saledate] [smalldatetime] NOT NULL,
	[price] [real] NOT NULL,
	[totqty] [int] NOT NULL,
	[totprice] [real] NOT NULL,
	[description] [nvarchar](300) NULL,
 CONSTRAINT [PK_sale_1] PRIMARY KEY CLUSTERED 
(
	[saleid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[shopowner]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[shopowner](
	[userid] [nvarchar](50) NOT NULL,
	[password] [nvarchar](6) NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[sex] [nchar](2) NOT NULL,
	[age] [smallint] NOT NULL,
	[isadmin] [smallint] NOT NULL,
	[address] [nvarchar](500) NULL,
	[tel] [nvarchar](50) NULL,
	[email] [nvarchar](50) NULL,
 CONSTRAINT [PK_user] PRIMARY KEY CLUSTERED 
(
	[userid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[seq]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[seq](
	[id] [nvarchar](50) NOT NULL,
	[prefix] [nvarchar](50) NULL,
	[curval] [int] NOT NULL,
	[totlen] [int] NOT NULL,
 CONSTRAINT [PK_customerid_seq] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[item]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[item](
	[itemid] [nvarchar](50) NOT NULL,
	[ownerid] [nvarchar](50) NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[price] [float] NOT NULL,
	[qty] [int] NOT NULL,
	[discnt] [real] NOT NULL,
	[initqty] [int] NOT NULL,
	[description] [nvarchar](300) NULL,
	[mandte] [datetime] NULL,
	[expdte] [datetime] NULL,
 CONSTRAINT [PK_item] PRIMARY KEY CLUSTERED 
(
	[itemid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[rent]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[rent](
	[boxid] [nvarchar](50) NOT NULL,
	[renterid] [nvarchar](50) NOT NULL,
	[seqnum] [int] NOT NULL,
	[rentname] [nvarchar](50) NOT NULL,
	[payed] [int] NOT NULL,
	[price] [real] NOT NULL,
	[totprice] [real] NOT NULL,
	[dtefrm] [datetime] NOT NULL,
	[dteto] [datetime] NOT NULL,
	[description] [nvarchar](300) NULL,
 CONSTRAINT [PK_rent] PRIMARY KEY CLUSTERED 
(
	[boxid] ASC,
	[renterid] ASC,
	[seqnum] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[cost]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[cost](
	[costid] [nvarchar](50) NOT NULL,
	[class] [nvarchar](50) NOT NULL,
	[date] [datetime] NOT NULL,
	[qty] [real] NOT NULL,
	[coster] [nvarchar](50) NOT NULL,
	[description] [varbinary](300) NULL,
 CONSTRAINT [PK_cost] PRIMARY KEY CLUSTERED 
(
	[costid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[customer]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[customer](
	[customerid] [nvarchar](50) NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[sex] [nvarchar](50) NOT NULL,
	[age] [int] NOT NULL,
	[tel] [nvarchar](50) NULL,
	[email] [nvarchar](50) NULL,
	[address] [nvarchar](300) NULL,
	[loylevel] [int] NOT NULL,
	[description] [nvarchar](300) NULL,
	[joindate] [datetime] NOT NULL,
 CONSTRAINT [PK_customer] PRIMARY KEY CLUSTERED 
(
	[customerid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[box]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[box](
	[boxid] [nvarchar](50) NOT NULL,
	[ownerid] [nvarchar](50) NULL,
	[rentprice] [real] NOT NULL,
	[description] [nvarchar](300) NULL,
 CONSTRAINT [PK_box] PRIMARY KEY CLUSTERED 
(
	[boxid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
