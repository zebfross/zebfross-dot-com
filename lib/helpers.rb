include Nanoc::Helpers::Tagging
include Nanoc::Helpers::Rendering

def get_nav_tag(title, link, tab)
  if title == tab
    "<li class='ui-selected'><span>#{title}</span>"
  else
    "<li><a href='#{link}'>#{title}</a>"
  end
end

def get_subnav_tag(title, link, tab)
  get_nav_tag(title, link, tab) + "</li>"
end
